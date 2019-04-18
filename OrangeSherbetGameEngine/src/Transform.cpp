#include "Transform.h"

//Transform::Transform(cml::mat4f viewMat, glm::mat4 projectionMat) : position(cml::VEC3_ZERO), rotation(cml::QUAT_IDENTITY), scale(cml::VEC3_ONE), model(cml::mat4f()), view(viewMat), projection(projectionMat) {}
Transform::Transform(glm::mat4 viewMat, glm::mat4 projectionMat) : position(glm::vec3(0, 0, 0)), rotation(glm::angleAxis(0.0f, glm::vec3(1.0f, 0.0f, 0.0f))), scale(glm::vec3(1, 1, 1)), model(glm::mat4(1.0f)), view(viewMat), projection(projectionMat) 
{
	isDirty = true; //make the model on first need
}
//Transform::Transform(cml::vec3f p, cml::quatf r, cml::vec3f s) : position(p), rotation(r), scale(s) {}
//
//Transform::Transform(cml::vec3f p) : position(p), rotation(cml::QUAT_IDENTITY), scale(cml::VEC3_ONE) {}
//Transform::Transform(cml::vec3f p, cml::quatf r) : position(p), rotation(r), scale(cml::VEC3_ONE) {}
//Transform::Transform(cml::vec3f p, cml::vec3f s) : position(p), rotation(cml::QUAT_IDENTITY), scale(s) {}
//Transform::Transform(cml::quatf r, cml::vec3f s) : position(cml::VEC3_ZERO), rotation(r), scale(s) {}
//~Transform::Transform();

glm::vec3 Transform::GetLocalPosition() {
	return position;
}

const glm::vec3& Transform::GetLocalPosition() const {
	return position;
}

void Transform::SetLocalPosition(const glm::vec3 val) {
	position = val;
	isDirty = true;
}

void Transform::Translate(glm::vec3 val) {
	position += val;
	isDirty = true;
}

glm::quat Transform::GetLocalRotation() {
	return rotation;
}

const glm::quat& Transform::GetLocalRotation() const {
	return rotation;
}

void Transform::SetLocalRotation(const  glm::quat val) {
	rotation = val;
	isDirty = true;
}

void Transform::SetLocalRotation(const float angle, const glm::vec3 &axis) {
	rotation = glm::angleAxis(angle, axis);
	isDirty = true;
}

void Transform::SetLocalRotation(const glm::vec3 &eulerAngles) {
	glm::quat rotX = glm::angleAxis(eulerAngles.x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::quat rotY = glm::angleAxis(eulerAngles.y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::quat rotZ = glm::angleAxis(eulerAngles.z, glm::vec3(0.0f, 0.0f, 1.0f));

	rotation = rotZ * rotY * rotX;
	isDirty = true;
}

void Transform::SetLocalRotation(const float x, const float y, const float z) {
	glm::quat rotX = glm::angleAxis(x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::quat rotY = glm::angleAxis(y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::quat rotZ = glm::angleAxis(z, glm::vec3(0.0f, 0.0f, 1.0f));

	rotation = rotZ * rotY * rotX;
	isDirty = true;
}

glm::vec3 Transform::GetLocalScale() {
	return scale;
}

const glm::vec3& Transform::GetLocalScale() const {
	return scale;
}

void Transform::SetLocalScale(const glm::vec3 val) {
	scale = val;
	isDirty = true;
}

void Transform::SetLocalScale(const float x, const float y, const float z) {
	scale = glm::vec3(x,y,z);
	isDirty = true;
}


glm::mat4 Transform::GetMatrix() {
	if (isDirty)
		UpdateMatrix();
	return model;
}

void Transform::UpdateMatrix() {
	model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = model * glm::mat4_cast(rotation);
	//model = glm::rotate(model, glm::angle(rotation), glm::axis(rotation));
	model = glm::scale(model, scale);
	isDirty = false;
}
//void SetModelMatrix(cml::mat4f newModelMat) {
//	model = newModelMat;
//}

glm::mat4 Transform::GetViewMatrix() {
	return view;
}
void Transform::SetViewMatrix(glm::mat4 newViewMat) {
	view = newViewMat;
}

//glm::mat4 GetProjectionMatrix() { return projection; }
//void SetProjectionMatrix(glm::mat4 newProjectionMatrix) {
//	projection = newProjectionMatrix;
//}

glm::mat4 Transform::GetProjectionMatrix() {
	return projection;
}
void Transform::SetProjectionMatrix(glm::mat4 newProjectionMatrix) {
	projection = newProjectionMatrix;
}