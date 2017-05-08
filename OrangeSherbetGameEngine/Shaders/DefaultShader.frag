#version 410 core

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct PointLight {
    vec4 position;
	vec3 color;
	float intensity;
};

struct DirLight {
    vec4 direction;
	vec3 color;
	float intensity;
};

struct SpotLight {
    vec4 position;
    vec4 direction;
    vec3 color;     
	  
	float intensity;
	float cutOff;
	float outerCutOff;
}; 

subroutine vec3 AlbedoTextureMode();
subroutine uniform AlbedoTextureMode albedoTexMode;

subroutine vec3 SpecularTextureMode();
subroutine uniform SpecularTextureMode specTexMode;

uniform Material material;
uniform sampler2D depthMap;

uniform sampler2D t_albedo;
uniform sampler2D t_diffuse;
uniform sampler2D t_specular;
uniform sampler2D t_normal;
uniform sampler2D t_emissive;
uniform sampler2D t_height;


uniform PointLight pointLights[5];
uniform DirLight dirlights[5];
uniform SpotLight spotLights[5];

in vec3 fragmentPos;
in vec3 normalDir;
in vec2 texturePos;
in vec3 lightPos;

out vec4 color;

//add switches for each texture. If they have don't have it and if they do

subroutine(AlbedoTextureMode)
vec3 AlbedoTexEnabled(){
	return vec3(texture(t_albedo, texturePos));
}

subroutine(AlbedoTextureMode)
vec3 AlbedoTexDisabled(){
	return vec3(1,1,1);
}

subroutine(SpecularTextureMode)
vec3 SpecularTexEnabled(){
	return vec3(texture(t_specular, texturePos));
}

subroutine(SpecularTextureMode)
vec3 SpecularTexDisabled(){
	return vec3(1,1,1);
}

vec3 BlinnPhongPointLightADS( int lightIndex, vec3 fragPos, vec3 norm, vec3 viewDir) {
	vec3 lightSource = normalize( vec3(pointLights[lightIndex].position) - fragPos );
    vec3 lightReflected = reflect(-lightSource, norm );
	vec3 halfway = normalize(viewDir + lightSource);
	
	float distance = length( vec3(pointLights[lightIndex].position) - fragPos);
	float attenuation = 1.0f/(1.0f + 0.07f*distance + 0.017f*distance*distance);
	
	vec3 lightContribution = pointLights[lightIndex].color * pointLights[lightIndex].intensity;
		
	return lightContribution * (attenuation * (material.ambient + 
		material.diffuse * max( dot(lightSource, norm), 0.0f) + 
		material.specular * specTexMode() * pow( max( dot(norm, halfway), 0.0 ), material.shininess )));
	//dot(norm, halfway) -- for blinn phong style lighting.
}

vec3 DirectionalLightADS(int lightIndex, vec3 fragPos, vec3 norm, vec3 viewDir) {
	vec3 lightDir = normalize( vec3(-dirlights[lightIndex].direction));
    vec3 lightReflected = reflect(lightDir, norm );
	
	vec3 lightContribution = pointLights[lightIndex].color * pointLights[lightIndex].intensity;
		
	return lightContribution * (material.ambient + 
		material.diffuse * max( dot(lightDir, norm), 0.0f) + 
		material.specular * specTexMode() * pow( max( dot(lightReflected, viewDir), 0.0 ), material.shininess ));
}

vec3 SpotLightADS(int lightIndex, vec3 fragPos, vec3 norm, vec3 viewDir) {
	vec3 lightSource = normalize( vec3(spotLights[lightIndex].position) - fragPos );
	vec3 lightDir = normalize(vec3(-spotLights[lightIndex].direction)); 
    vec3 lightReflected = reflect(-lightSource, norm );
	vec3 halfway = normalize(viewDir + lightSource);

	float distance = length( vec3(spotLights[lightIndex].position) - fragPos);
	float attenuation = 1.0f/(1.0f + 0.07f*distance + 0.017f*distance*distance);

	vec3 lightContribution = spotLights[lightIndex].color * spotLights[lightIndex].intensity;

	float theta = acos(  dot(lightSource, lightDir)); 
    float epsilon = (spotLights[lightIndex].cutOff - spotLights[lightIndex].outerCutOff);
    float spotIntensity = clamp((theta - spotLights[lightIndex].outerCutOff) / epsilon, 0.0, 1.0);

	return lightContribution * (spotIntensity * attenuation * (material.ambient + 
			material.diffuse * max( dot(lightSource, norm), 0.0f) + 
			material.specular * specTexMode() * pow( max( dot(norm, halfway), 0.0 ), material.shininess )));
		
	
}

void main() {
	
	vec3 norm = normalize(normalDir);
	vec3 viewDir = normalize(vec3(-fragmentPos));

	vec3 result = vec3(0.0);    
	for( int i = 0; i < 5; i++ ) {       
		result += BlinnPhongPointLightADS( i, fragmentPos, norm, viewDir);
	}

	for(int i = 0; i < 5; i++) {
		result += DirectionalLightADS(i, fragmentPos, norm, viewDir);
	}

	for(int i = 0; i < 5; i++){
		result += SpotLightADS(i, fragmentPos, norm, viewDir);
	}
	
	result *= albedoTexMode();

	float gamma = 2.2;
    result = pow(result, vec3(1.0/gamma));

	color = vec4(result, 1.0f);

}

//gets the depth of each pixel, reajusted to be in world(ish) space
vec4 depthTestLinearized(float zCoord){
	float near = 1.0; 
	float far  = 100.0; 
	
	float z = zCoord * 2.0 - 1.0; // Back to NDC 
	float depth = (2.0 * near * far) / (far + near - z * (far - near))/ far;	
	return 	vec4(vec3(depth),1.0f);
}