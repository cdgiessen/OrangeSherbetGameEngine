#pragma once

#ifndef TRANSFORM_H

#include <CML\cml.h>

namespace Osge {

	class Transform
	{
	public:
		Transform() : position(cml::VEC3_ZERO), rotation(cml::QUAT_IDENTITY), scale(cml::VEC3_ONE) {}
		Transform(cml::vec3<float> p, cml::quat<float> r, cml::vec3<float> s) : position(p), rotation(r), scale(s) {}

		Transform(cml::vec3<float> p) : position(p), rotation(cml::QUAT_IDENTITY), scale(cml::VEC3_ONE) {}
		Transform(cml::vec3<float> p, cml::quat<float> r) : position(p), rotation(r), scale(cml::VEC3_ONE) {}
		Transform(cml::vec3<float> p, cml::vec3<float> s) : position(p), rotation(cml::QUAT_IDENTITY), scale(s) {}
		Transform(cml::quat<float> r, cml::vec3<float> s) : position(cml::VEC3_ZERO), rotation(r), scale(s) {}
		~Transform();

		cml::vec3<float> position;
		cml::quat<float> rotation;
		cml::vec3<float> scale;
	};

}

#endif // !TRANSFORM_H
