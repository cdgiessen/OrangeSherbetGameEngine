#version 400 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct PointLight {
    vec3 position;
	vec3 color;
    
    float constant;
    float linear;
    float quadratic;
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
uniform Material material;

uniform sampler2D t_albedo;
uniform sampler2D t_diffuse;
uniform sampler2D t_specular;
uniform sampler2D t_normal;

uniform PointLight pointLights[5];
uniform DirLight dirlight[5];
uniform SpotLight spotLights[5];

in vec3 fragmentPos;
in vec3 normalDir;
in vec2 texturePos;
in vec3 lightPos;

out vec4 color;


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
	float specularStrength = 0.5f;
    vec3 viewDir = normalize(-fragmentPos); // The viewer is at (0,0,0) so viewDir is (0,0,0) - Position => -Position
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * vec3(1,1,1); 

	vec3 result = (ambient + diffuse) * albedoColor;
	color = vec4(result, 1.0f);


}
