#pragma once

#include <glm\vec3.hpp>
#include <glm\vec4.hpp>

class Color
{
public:
	float r;
	float g;
	float b;
	float a;
		
	Color(float r, float g, float b);
	~Color();

	glm::vec4 ToVec4();

	glm::vec3 ToVec3();


};


