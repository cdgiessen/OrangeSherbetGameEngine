#version 410 core

//struct Material {
uniform    vec3 m_ambient;
uniform    vec3 m_diffuse;
uniform    vec3 m_specular;
uniform    float m_shininess;
//};

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

uniform vec3 viewPos;
//uniform Material material;

uniform sampler2D t_albedo;
uniform sampler2D t_diffuse;
uniform sampler2D t_specular;
uniform sampler2D t_normal;

uniform PointLight pointLights[5];
uniform DirLight dirlights[5];
uniform SpotLight spotLights[5];

in vec3 fragmentPos;
in vec3 normalDir;
in vec2 texturePos;
in vec3 lightPos;

out vec4 color;

vec3 PointLightADS( int lightIndex, vec3 fragPos, vec3 norm, vec3 viewDir)
{
    vec3 lightSource = normalize( vec3(pointLights[lightIndex].position) - fragPos );
    vec3 lightReflected = reflect( -lightSource, norm );
	
	float distance = length( vec3(pointLights[lightIndex].position) - fragPos);
	float attenuation = 1.0f/(1.0f + 0.07f*distance + 0.017f*distance*distance);
	
	return pointLights[lightIndex].color * pointLights[lightIndex].intensity * 
		(m_ambient * attenuation + 
		m_diffuse * attenuation * max( dot(lightSource, norm), 0.0f) + 
		m_specular * attenuation * vec3(texture(t_specular, texturePos)) * 
			pow( max( dot(lightReflected, viewDir), 0.0 ), m_shininess ));
}

void main() {
	
	vec3 albedoColor = vec3(texture(t_albedo, texturePos));

	vec3 norm = normalize(normalDir);
	vec3 viewDir = normalize(vec3(-fragmentPos));

	vec3 result = vec3(0.0);    
	for( int i = 0; i < 5; i++ ) {       
		result += PointLightADS( i, fragmentPos, norm, viewDir);
	}
	
	result *= albedoColor;

	color = vec4(result, 1.0f);


}
