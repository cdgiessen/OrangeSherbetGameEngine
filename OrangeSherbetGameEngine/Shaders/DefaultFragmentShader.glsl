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

vec3 ads( int lightIndex, vec3 position ,vec3 norm )
{
    vec3 lightSource = normalize( vec3(pointLights[lightIndex].position) - position );
    vec3 lightReflected = reflect( -lightSource, norm );
    vec3 viewer = normalize(vec3(-position));
	vec3 lightColor = pointLights[lightIndex].color;
    float brightness = pointLights[lightIndex].intensity;

	float distance = length( vec3(pointLights[lightIndex].position) - position);
	float attenuation = 1.0f/(1.0f + 0.07*distance + 0.017*distance*distance);
    
	return lightColor * brightness *  ( m_ambient* attenuation + m_diffuse* attenuation * max( dot(lightSource, norm), 0.0 ) + m_specular * pow( max( dot(lightReflected,viewer), 0.0 ), m_shininess )* attenuation  );
}

void main() {
	
	vec3 albedoColor = vec3(texture(t_albedo, texturePos));

	vec3 norm = normalize(normalDir);
    vec3 lightDir = normalize(lightPos - fragmentPos);
	
	//ambient
	float ambientStrength = 0.05f;
    vec3 ambient = ambientStrength * vec3(1,1,1);
	
	//diffuse
	float diffuseStrength = 0.5f;
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1,1,1);

	//specular
	float specularStrength = 1.0f;
    vec3 viewDir = normalize(-fragmentPos); // The viewer is at (0,0,0) so viewDir is (0,0,0) - Position => -Position
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * vec3(texture(t_specular, texturePos)) * spec * vec3(1,1,1); 
	
	vec3 Color = vec3(0.0);    
	for( int i = 0; i < 5; i++ ) {       
		Color += ads( i, fragmentPos, norm );
	}

	vec3 result = (ambient + diffuse +  specular) * albedoColor;
	
	color = vec4(Color, 1.0f);


}
