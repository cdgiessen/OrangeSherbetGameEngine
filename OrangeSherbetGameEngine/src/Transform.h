#pragma once

#ifndef TRANSFORM_H
#define TRANSFORM_H

//#include <CML\cml.h>
//#include <CML\vec3.h>
//#include <CML\mat4.h>
//#include <CML\quat.h>
#include <vector>

//Temporary
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform
{
public:
	//Transform(cml::mat4f viewMat, glm::mat4 projectionMat) : position(cml::VEC3_ZERO), rotation(cml::QUAT_IDENTITY), scale(cml::VEC3_ONE), model(cml::mat4f()), view(viewMat), projection(projectionMat) {}
	Transform(glm::mat4 viewMat, glm::mat4 projectionMat) : position(glm::vec3(0,0,0)), rotation(glm::quat(0,0,0,1)), scale(glm::vec3(1,1,1)), model(glm::mat4()), view(viewMat), projection(projectionMat) {}
	//Transform(cml::vec3f p, cml::quatf r, cml::vec3f s) : position(p), rotation(r), scale(s) {}
	//
	//Transform(cml::vec3f p) : position(p), rotation(cml::QUAT_IDENTITY), scale(cml::VEC3_ONE) {}
	//Transform(cml::vec3f p, cml::quatf r) : position(p), rotation(r), scale(cml::VEC3_ONE) {}
	//Transform(cml::vec3f p, cml::vec3f s) : position(p), rotation(cml::QUAT_IDENTITY), scale(s) {}
	//Transform(cml::quatf r, cml::vec3f s) : position(cml::VEC3_ZERO), rotation(r), scale(s) {}
	//~Transform();

	glm::vec3 GetLocalPosition() {
		return position;
	}

	const glm::vec3& GetLocalPosition() const {
		return position;
	}

	void SetLocalPosition(const glm::vec3 val) {
		position = val;
		isDirty = true;
	}

	void Translate(glm::vec3 val) {
		position += val;
		isDirty = true;
	}

	glm ::quat GetLocalRotation() {
		return rotation;
	}

	const glm::quat& GetLocalRotation() const {
		return rotation;
	}

	void SetLocalRotation(const  glm::quat val) {
		rotation = val;
		isDirty = true;
	}

	//void SetLocalRotation(const glm::vec3 axis, const float angle) {
	//	rotation = glm::quat(axis, angle);
	//}
	//
	//void SetLocalRotation(const glm::vec3 eulerAngles) {
	//	rotation = glm ::quat(eulerAngles);
	//}

	glm::vec3 GetLocalScale() {
		return scale;
	}

	const glm::vec3& GetLocalScale() const {
		return scale;
	}

	void SetLocalScale(const glm::vec3 val) {
		scale = val;
		isDirty = true;
	}


	glm::mat4 GetMatrix() {
		if (isDirty)
			UpdateMatrix();
		return model;
	}

	void UpdateMatrix() {
		model = glm::translate(model, position);
		model = glm::rotate(model, glm::angle(rotation), glm::axis(rotation));
		model = glm::scale(model, scale);
		isDirty = false;
	}
	//void SetModelMatrix(cml::mat4f newModelMat) {
	//	model = newModelMat;
	//}

	glm::mat4 GetViewMatrix() {
		return view; 
	}
	void SetViewMatrix(glm::mat4 newViewMat) {
		view = newViewMat;
	}

	//glm::mat4 GetProjectionMatrix() { return projection; }
	//void SetProjectionMatrix(glm::mat4 newProjectionMatrix) {
	//	projection = newProjectionMatrix;
	//}

	glm::mat4 GetProjectionMatrix() {
		return projection; 
	}
	void SetProjectionMatrix(glm::mat4 newProjectionMatrix) {
		projection = newProjectionMatrix;
	}

private:
	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;

	bool isDirty; //if the model has updated and needs to be recalculated
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	//glm::mat4 projection;
	
	//Transform &parent;
	//std::vector<Transform> children;
};



#endif // !TRANSFORM_H
