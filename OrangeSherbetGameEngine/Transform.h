#pragma once

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <CML\cml.h>

#include <vector>

namespace Osge {

	class Transform
	{
	public:
		Transform() : position(cml::VEC3_ZERO), rotation(cml::QUAT_IDENTITY), scale(cml::VEC3_ONE) {}
		Transform(cml::vec3f p, cml::quatf r, cml::vec3f s) : position(p), rotation(r), scale(s) {}
						   
		Transform(cml::vec3f p) : position(p), rotation(cml::QUAT_IDENTITY), scale(cml::VEC3_ONE) {}
		Transform(cml::vec3f p, cml::quatf r) : position(p), rotation(r), scale(cml::VEC3_ONE) {}
		Transform(cml::vec3f p, cml::vec3f s) : position(p), rotation(cml::QUAT_IDENTITY), scale(s) {}
		Transform(cml::quatf r, cml::vec3f s) : position(cml::VEC3_ZERO), rotation(r), scale(s) {}
		//~Transform();

		cml::vec3f GetLocalPosition() {
			return position;
		}

		const cml::vec3f& GetLocalPosition() const{
			return position;
		}

		void SetLocalPosition(const cml::vec3f val) {
			position = val;
		}

		cml::quatf GetLocalRotation() {
			return rotation;
		}

		const cml::quatf& GetLocalRotation() const {
			return rotation;
		}

		void SetLocalRotation(const  cml::quatf val) {
			rotation = val;
		}

		cml::vec3f GetLocalScale() {
			return scale;
		}

		const cml::vec3f& GetLocalScale() const {
			return scale;
		}

		void SetLocalRotation(const cml::vec3f val) {
			scale = scale;
		}

	private:
		cml::vec3<float> position;
		cml::quat<float> rotation;
		cml::vec3<float> scale;

		//Transform &parent;
		//std::vector<Transform> children;
	};

}

#endif // !TRANSFORM_H
