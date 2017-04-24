#pragma once


#include <glm\vec3.hpp>
#include <glm\vec4.hpp>
#include "Color.h"
#include "GLSLProgram.h"

class Light
{
public:
	enum LightType {
		Point,
		Spot,
		Dir
	};

	Light(Color col, glm::vec3 pos, glm::vec3 dir, float intense, LightType type);
	Light(Color col, glm::vec3 pos, glm::vec3 dir, float intense, float cut, float outCut, Light::LightType type);


	Light();
	~Light();

	LightType GetLightType();

	Color GetColor();
	void SetColor(Color color);

	glm::vec3 GetPosition();
	void SetPosition(glm::vec3 pos);

	glm::vec3 GetDirection();
	void SetDirection(glm::vec3 dir);

	float GetIntensity();
	void SetIntensity(float intense);

	float GetCutOff();
	void SetCutOff(float val);

	float GetOuterCutOff();
	void SetOuterCutOff(float val);

	void FillUniform(GLSLProgram *shader, int place, glm::mat4 eyeSpace);

private:
	Light::LightType lightType = LightType::Point;

	float intensity;
	Color lightColor;

	glm::vec3 position;
	glm::vec3 direction;

	//For spotlights
	float cutOff;
	float outerCutOff;
};

