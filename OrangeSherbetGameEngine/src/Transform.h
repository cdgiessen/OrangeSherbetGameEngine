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
#include <glm\gtc\quaternion.hpp>
//#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform
{
public:
	//Transform(cml::mat4f viewMat, glm::mat4 projectionMat) : position(cml::VEC3_ZERO), rotation(cml::QUAT_IDENTITY), scale(cml::VEC3_ONE), model(cml::mat4f()), view(viewMat), projection(projectionMat) {}
	Transform(glm::mat4 viewMat, glm::mat4 projectionMat);
	//Transform(cml::vec3f p, cml::quatf r, cml::vec3f s) : position(p), rotation(r), scale(s) {}
	//
	//Transform(cml::vec3f p) : position(p), rotation(cml::QUAT_IDENTITY), scale(cml::VEC3_ONE) {}
	//Transform(cml::vec3f p, cml::quatf r) : position(p), rotation(r), scale(cml::VEC3_ONE) {}
	//Transform(cml::vec3f p, cml::vec3f s) : position(p), rotation(cml::QUAT_IDENTITY), scale(s) {}
	//Transform(cml::quatf r, cml::vec3f s) : position(cml::VEC3_ZERO), rotation(r), scale(s) {}
	//~Transform();

	glm::vec3 GetLocalPosition();

	const glm::vec3& GetLocalPosition() const;

	void SetLocalPosition(const glm::vec3 val);

	void Translate(glm::vec3 val);

	glm::quat GetLocalRotation();

	const glm::quat& GetLocalRotation() const;

	void SetLocalRotation(const  glm::quat val);

	//void SetLocalRotation(const glm::vec3 axis, const float angle) {
	//	rotation = glm::quat(axis, angle);
	//}
	//
	//void SetLocalRotation(const glm::vec3 eulerAngles) {
	//	rotation = glm ::quat(eulerAngles);
	//}

	glm::vec3 GetLocalScale();

	const glm::vec3& GetLocalScale() const;

	void SetLocalScale(const glm::vec3 val);


	glm::mat4 GetMatrix();

	void UpdateMatrix();
	//void SetModelMatrix(cml::mat4f newModelMat);

	glm::mat4 GetViewMatrix();

	void SetViewMatrix(glm::mat4 newViewMat);

	//glm::mat4 GetProjectionMatrix();
	//void SetProjectionMatrix(glm::mat4 newProjectionMatrix);

	glm::mat4 GetProjectionMatrix();

	void SetProjectionMatrix(glm::mat4 newProjectionMatrix);

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
