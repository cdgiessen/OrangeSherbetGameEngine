#pragma once

#include <glm\vec3.hpp>
#include "Color.h"

class Light
{
public:
	enum LightType {
		Point,
		Spot,
		Dir
	};

	Light::LightType type;

	Light();
	~Light();

	Color GetColor();
	void SetColor(Color color);

	glm::vec3 GetPosition();
	void SetPosition(glm::vec3 pos);

	glm::vec3 GetDirection();
	void SetDirection(glm::vec3 dir);

private:
	float intensity;
	Color lightColor;

	glm::vec3 position;
	glm::vec3 direction;
};

