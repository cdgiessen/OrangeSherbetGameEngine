#include "../include/GameObject.h"



GameObject::GameObject(Transform *transform, Mesh *mesh, Shader *shader) : transform(transform), mesh(mesh), shader(shader)
{
}


GameObject::~GameObject()
{
}

void GameObject::Draw(cml::mat4f newViewMatrix) {

	shader->Use();

	transform->SetViewMatrix(newViewMatrix);

	GLint modelLoc = glGetUniformLocation(shader->Program, "model");
	GLint viewLoc = glGetUniformLocation(shader->Program, "view");
	GLint projLoc = glGetUniformLocation(shader->Program, "projection");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, cml::mat4f::value_ptr(transform->GetModelMatrix()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, cml::mat4f::value_ptr(transform->GetProjectionMatrix()));
	//glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(transform->GetProjectionMatrix()));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, cml::mat4f::value_ptr(transform->GetViewMatrix()));

	mesh->Draw(*shader);
}