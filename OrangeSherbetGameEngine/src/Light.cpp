#include "Light.h"



Light::Light() : lightColor(Color(1.0f,1.0f,1.0f)), position(glm::vec3(0,0,0)), direction(glm::vec3(0,-90,0)), intensity(0.5f), lightType(Light::LightType::Point)
{
}

Light::Light(Color col, glm::vec3 pos, glm::vec3 dir, float intense, Light::LightType type) : lightColor(col), position(pos), direction(dir), intensity(intense), lightType(type)
{
}

Light::Light(Color col, glm::vec3 pos, glm::vec3 dir, float intense, float cut, float outCut, Light::LightType type) : lightColor(col), position(pos), direction(dir), intensity(intense), cutOff(cut), outerCutOff(outCut), lightType(type)
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

void Light::SetIntensity(float intense) {
	intensity = intense;
}

float Light::GetCutOff()
{
	return cutOff;
}

void Light::SetCutOff(float val) {
	cutOff = val;
}

float Light::GetOuterCutOff() {
	return outerCutOff;
}

void Light::SetOuterCutOff(float val) {
	outerCutOff = val;
}

//Fills this light into the appropriate uniform buffers at place i in the lights array
void Light::FillUniform(GLSLProgram *shader, int i, glm::mat4 eyeSpace) {
	std::string name;
	switch (this->lightType) {
		case(LightType::Point):
			name = "pointLights[" + std::to_string(i) + "].position";
			shader->setUniform(name.c_str(), eyeSpace*glm::vec4(position,1.0f));

			name = "pointLights[" + std::to_string(i) + "].color";
			shader->setUniform(name.c_str(), GetColor().ToVec3());

			name = "pointLights[" + std::to_string(i) + "].intensity";
			shader->setUniform(name.c_str(), intensity);
			break;
		
		case(LightType::Dir):
			name = "dirlights[" + std::to_string(0) + "].direction";
			shader->setUniform(name.c_str(), eyeSpace*glm::vec4(direction, 0.0f));
		
			name = "dirlights[" + std::to_string(0) + "].color";
			shader->setUniform(name.c_str(), GetColor().ToVec3());
		
			name = "dirlights[" + std::to_string(0) + "].intensity";
			shader->setUniform(name.c_str(), intensity);
			break;
		
		case(LightType::Spot):
			name = "spotLights[" + std::to_string(0) + "].position";
			shader->setUniform(name.c_str(), eyeSpace*glm::vec4(position, 1.0f));

			name = "spotLights[" + std::to_string(0) + "].direction";
			shader->setUniform(name.c_str(), eyeSpace*glm::vec4(direction, 0.0f));

			name = "spotLights[" + std::to_string(0) + "].color";
			shader->setUniform(name.c_str(), GetColor().ToVec3());

			name = "spotLights[" + std::to_string(0) + "].intensity";
			shader->setUniform(name.c_str(), intensity);

			name = "spotLights[" + std::to_string(0) + "].cutOff";
			shader->setUniform(name.c_str(), cutOff);

			name = "spotLights[" + std::to_string(0) + "].outerCutOff";
			shader->setUniform(name.c_str(), outerCutOff);
			break;

	}
}