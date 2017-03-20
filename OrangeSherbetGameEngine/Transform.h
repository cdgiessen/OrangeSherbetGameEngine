#pragma once

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <CML\cml.h>

#include <vector>

//Temporary
#include <glm\glm.hpp>

class Transform
{
public:
	Transform(cml::mat4f viewMat, glm::mat4 projectionMat) : position(cml::VEC3_ZERO), rotation(cml::QUAT_IDENTITY), scale(cml::VEC3_ONE), model(cml::mat4f()), view(viewMat), projection(projectionMat) {}
	//Transform(cml::vec3f p, cml::quatf r, cml::vec3f s) : position(p), rotation(r), scale(s) {}
	//
	//Transform(cml::vec3f p) : position(p), rotation(cml::QUAT_IDENTITY), scale(cml::VEC3_ONE) {}
	//Transform(cml::vec3f p, cml::quatf r) : position(p), rotation(r), scale(cml::VEC3_ONE) {}
	//Transform(cml::vec3f p, cml::vec3f s) : position(p), rotation(cml::QUAT_IDENTITY), scale(s) {}
	//Transform(cml::quatf r, cml::vec3f s) : position(cml::VEC3_ZERO), rotation(r), scale(s) {}
	//~Transform();

	cml::vec3f GetLocalPosition() {
		return position;
	}

	const cml::vec3f& GetLocalPosition() const {
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


	cml::mat4f GetModelMatrix() { return model; }
	void UpdateModelMatrix() {
		//Create model matrix here
	}
	void SetModelMatrix(cml::mat4f newModelMat) {
		model = newModelMat;
	}

	cml::mat4f GetViewMatrix() { return view; }
	void SetViewMatrix(cml::mat4f newViewMat) {
		view = newViewMat;
	}

	glm::mat4 GetProjectionMatrix() { return projection; }
	void SetProjectionMatrix(glm::mat4 newProjectionMatrix) {
		projection = newProjectionMatrix;
	}

private:
	cml::vec3<float> position;
	cml::quat<float> rotation;
	cml::vec3<float> scale;

	cml::mat4f model;
	cml::mat4f view;
	glm::mat4 projection;

	//Transform &parent;
	//std::vector<Transform> children;
};



#endif // !TRANSFORM_H
