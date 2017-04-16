#include "Color.h"



Color::Color(float r, float g, float b) : r(r), g(g), b(b), a(1.0f)
{
}


Color::~Color()
{
}

glm::vec4 Color::ToVec4() {
	return glm::vec4(r, g, b, a);
}

glm::vec3 Color::ToVec3() {
	return glm::vec3(r, g, b);
}
