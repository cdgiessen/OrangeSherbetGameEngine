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
    vec3 direction;
	vec3 color;
	float intensity;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
	float outerCutOff;
    
    float constant;
    float linear;
    float quadratic;
    
    vec3 color;       
}; 

subroutine vec3 PointLightTextureMode( int lightIndex, vec3 fragPos, vec3 norm, vec3 viewDir);
subroutine uniform PointLightTextureMode pointLightTexMode;

uniform Material material;

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

subroutine(PointLightTextureMode)
vec3 PointLightADS( int lightIndex, vec3 fragPos, vec3 norm, vec3 viewDir)
{
    vec3 lightSource = normalize( vec3(pointLights[lightIndex].position) - fragPos );
    vec3 lightReflected = reflect( -lightSource, norm );
	vec3 halfway = normalize(viewDir + lightSource);
	
	float distance = length( vec3(pointLights[lightIndex].position) - fragPos);
	float attenuation = 1.0f/(1.0f + 0.07f*distance + 0.017f*distance*distance);
	
	return pointLights[lightIndex].color * pointLights[lightIndex].intensity * 
		(material.ambient * attenuation + 
		material.diffuse * attenuation * max( dot(lightSource, norm), 0.0f) + 
		material.specular * attenuation * vec3(texture(t_specular, texturePos)) * 
			pow( max( dot(norm, halfway), 0.0 ), material.shininess ));
}

subroutine(PointLightTextureMode)
vec3 PointLightADSNoSpecTexture( int lightIndex, vec3 fragPos, vec3 norm, vec3 viewDir)
{
    vec3 lightSource = normalize( vec3(pointLights[lightIndex].position) - fragPos );
    vec3 lightReflected = reflect( -lightSource, norm );
	vec3 halfway = normalize(viewDir + lightSource);
	
	float distance = length( vec3(pointLights[lightIndex].position) - fragPos);
	float attenuation = 1.0f/(1.0f + 0.07f*distance + 0.017f*distance*distance);
	
	return pointLights[lightIndex].color * pointLights[lightIndex].intensity * 
		(material.ambient * attenuation + 
		material.diffuse * attenuation * max( dot(lightSource, norm), 0.0f) + 
		material.specular * attenuation * //vec3(texture(t_specular, texturePos)) * 
			pow( max( dot(norm, halfway), 0.0 ), material.shininess ));
}

void main() {
	
	vec3 albedoTexColor = vec3(texture(t_albedo, texturePos));
	vec3 diffuseTexColor = vec3(texture(t_diffuse, texturePos));
	vec3 specularTexColor = vec3(texture(t_specular, texturePos));


	vec3 norm = normalize(normalDir);
	vec3 viewDir = normalize(vec3(-fragmentPos));

	vec3 result = vec3(0.0);    
	for( int i = 0; i < 5; i++ ) {       
		result += pointLightTexMode( i, fragmentPos, norm, viewDir);
	}
	
	//result *= albedoTexColor;

	color = vec4(result, 1.0f);


}
