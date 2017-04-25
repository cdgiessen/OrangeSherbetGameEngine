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

namespace Colors {

	static const Color RED(1.0f, 0.0f, 0.0f);
	static const Color GREEN(0.0f, 1.0f, 0.0f);
	static const Color BLUE(0.0f, 0.0f, 1.0f);

	static const Color YELLOW(1.0f, 1.0f, 0.0f);
	static const Color MAGENTA(1.0f, 0.0f, 1.0f);
	static const Color CYAN(0.0f, 1.0f, 1.0f);

	static const Color BLACK(0.0f, 0.0f, 0.0f);
	static const Color GREY(0.5f, 0.5f, 0.5f);
	static const Color WHITE(1.0f, 1.0f, 1.0f);

}