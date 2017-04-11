#include "Light.h"



Light::Light() : lightColor(Color(1.0f,1.0f,1.0f)), intensity(1.0f)
{
}


Light::~Light()
{
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
