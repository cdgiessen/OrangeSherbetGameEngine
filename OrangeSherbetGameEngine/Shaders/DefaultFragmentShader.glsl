#version 400 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
	vec3 color;
};

struct DirLight {
    vec3 direction;
	vec3 color;


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

in vec3 fragmentPos;
in vec3 normal;
in vec2 texturePos;

in vec3 LightIntensity;

out vec4 color;

uniform vec3 viewPos;
uniform Material material;

uniform sampler2D t_albedo;
uniform sampler2D t_diffuse;
uniform sampler2D t_specular;
uniform sampler2D t_normal;

uniform PointLight pointLights[5];
uniform DirLight dirlight;
uniform SpotLight spotLight;

void main() {
	
	vec3 result = vec3(texture(t_albedo, texturePos));
	color = vec4(LightIntensity*result, 1.0f);


}
