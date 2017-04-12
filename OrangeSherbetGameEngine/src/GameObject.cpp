#include "GameObject.h"

#include <glm/gtc/type_ptr.hpp>

GameObject::GameObject(Transform *transform, Mesh *mesh, Shader *shader) : transform(transform), mesh(mesh), shader(shader)
{
}


GameObject::~GameObject()
{
}

void GameObject::Draw(glm::mat4 newViewMatrix) {

	shader->Use();

	transform->SetViewMatrix(newViewMatrix);

	GLint modelLoc = glGetUniformLocation(shader->Program, "model");
	GLint viewLoc = glGetUniformLocation(shader->Program, "view");
	GLint projLoc = glGetUniformLocation(shader->Program, "projection");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform->GetMatrix()));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(transform->GetViewMatrix()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(transform->GetProjectionMatrix()));

	mesh->Draw(*shader);
}