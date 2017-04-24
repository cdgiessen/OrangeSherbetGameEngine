#include "Light.h"



Light::Light() : lightColor(Color(1.0f,1.0f,1.0f)), position(glm::vec3(0,0,0)), direction(glm::vec3(0,-1,0)), intensity(0.5f), lightType(Light::LightType::Point)
{
}

Light::Light(Color col, glm::vec3 pos, glm::vec3 dir, float intense, Light::LightType type) : lightColor(col), position(pos), direction(dir), intensity(intense), lightType(type) 
{
}


Light::~Light()
{
}

Light::LightType Light::GetLightType()
{
	return lightType;
}

Color Light::GetColor() {
	return lightColor;
}

void Light::SetColor(Color color) {
	lightColor = color;
}

glm::vec3 Light::GetPosition()
{
	return position;
}

void Light::SetPosition(glm::vec3 pos)
{
	position = pos;
}

glm::vec3 Light::GetDirection()
{
	return direction;
}

void Light::SetDirection(glm::vec3 dir)
{
	direction = dir;
}

float Light::GetIntensity()
{
	return intensity;
}

void Light::SetIntensity(float intense)
{
	intensity = intense;
}

//Fills this light into the appropriate uniform buffers at place i in the lights array
void Light::FillUniform(GLSLProgram *shader, int i, glm::mat4 eyeSpace) {
	std::stringstream name;
	switch (lightType) {
		case(LightType::Point):
			name << "pointLights[" << i << "].position";
			shader->setUniform(name.str().c_str(), eyeSpace*glm::vec4(position,1.0f));
			name.clear();
			name << "pointLights[" << i << "].color";
			shader->setUniform(name.str().c_str(), GetColor().ToVec3());
			name.clear();
			name << "pointLights[" << i << "].intensity";
			shader->setUniform(name.str().c_str(), intensity);
			break;
		
		case(LightType::Dir):
			name << "dirlights[" << i << "].direction";
			shader->setUniform(name.str().c_str(), glm::vec3(eyeSpace*glm::vec4(direction, 1.0f)));
			name.clear();
			name << "dirlights[" << i << "].color";
			shader->setUniform(name.str().c_str(), GetColor().ToVec3());
			name.clear();
			name << "dirlights[" << i << "].intensity";
			shader->setUniform(name.str().c_str(), intensity);
			break;
		
		case(LightType::Spot):
			//name << "lights[" << i << "].position";
			//shader->setUniform(name.str().c_str(), position);
			//name.clear();
			//name << "lights[" << i << "].color";
			//shader->setUniform(name.str().c_str(), GetColor().ToVec3());
			//name.clear();
			//name << "lights[" << i << "].intensity";
			//shader->setUniform(name.str().c_str(), intensity);
			break;

	}
}