#include "GameObject.h"

#include <glm/gtc/type_ptr.hpp>

GameObject::GameObject(Transform *transform, Mesh *mesh, GLSLProgram *shader) : transform(transform), mesh(mesh), shader(shader)
{
}


GameObject::~GameObject()
{
}

void GameObject::Draw(glm::mat4 newViewMatrix, std::vector<Light> *listOfLights) {

	shader->use();

	transform->SetViewMatrix(newViewMatrix);
	
	//GLuint blockIndex = glGetUniformBlockIndex(shader->Program, "MVPUniform");
	//
	//GLint blockSize;
	//glGetActiveUniformBlockiv(shader->Program, blockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);
	//GLubyte * blockBuffer = (GLubyte *)malloc(blockSize);
	//std::cout << blockSize << std::endl;
	//
	//const GLchar *names[] = { "model", "view", "proj"}; 
	//GLuint indices[3]; 
	//glGetUniformIndices(shader->Program, 3, names, indices); 
	//GLint offset[3]; 
	//glGetActiveUniformsiv(shader->Program, 3, indices, GL_UNIFORM_OFFSET, offset);
	//
	//memcpy(blockBuffer + offset[0], glm::value_ptr(transform->GetMatrix()), 16*sizeof(GLfloat));
	//memcpy(blockBuffer + offset[1], glm::value_ptr(transform->GetViewMatrix()), 16 * sizeof(GLfloat));
	//memcpy(blockBuffer + offset[2], glm::value_ptr(transform->GetProjectionMatrix()), 16 * sizeof(GLfloat));
	//
	//GLuint uboHandle; 
	//glGenBuffers(1, &uboHandle); 
	//glBindBuffer(GL_UNIFORM_BUFFER, uboHandle); 
	//glBufferData(GL_UNIFORM_BUFFER, blockSize, blockBuffer, GL_DYNAMIC_DRAW);
	//
	//glBindBufferBase(GL_UNIFORM_BUFFER, blockIndex, uboHandle);

	/*
	GLint modelLoc = glGetUniformLocation(shader->getHandle(), "model");
	GLint viewLoc = glGetUniformLocation(shader->getHandle(), "view");
	GLint projLoc = glGetUniformLocation(shader->getHandle(), "proj");
	
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform->GetMatrix()));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(transform->GetViewMatrix()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(transform->GetProjectionMatrix()));
	*/
	shader->setUniform("model", (transform->GetMatrix()));
	shader->setUniform("view", (transform->GetViewMatrix()));
	shader->setUniform("proj", (transform->GetProjectionMatrix()));

	//for (int i = 0; i < listOfLights->size(); i++) {
	//	(*listOfLights)[i].FillUniform(shader, i, eyespace);
	//}

	shader->setUniform("pointLights[0].position", transform->GetViewMatrix() * glm::vec4((*listOfLights)[0].GetPosition(), 1.0f));
	shader->setUniform("pointLights[1].position", transform->GetViewMatrix() * glm::vec4((*listOfLights)[1].GetPosition(), 1.0f));
	shader->setUniform("pointLights[2].position", transform->GetViewMatrix() * glm::vec4((*listOfLights)[2].GetPosition(), 1.0f));
	shader->setUniform("pointLights[3].position", transform->GetViewMatrix() * glm::vec4((*listOfLights)[3].GetPosition(), 1.0f));
	shader->setUniform("pointLights[4].position", transform->GetViewMatrix() * glm::vec4((*listOfLights)[4].GetPosition(), 1.0f));

	shader->setUniform("pointLights[0].color", (*listOfLights)[0].GetColor().ToVec3());
	shader->setUniform("pointLights[1].color", (*listOfLights)[1].GetColor().ToVec3());
	shader->setUniform("pointLights[2].color", (*listOfLights)[2].GetColor().ToVec3());
	shader->setUniform("pointLights[3].color", (*listOfLights)[3].GetColor().ToVec3());
	shader->setUniform("pointLights[4].color", (*listOfLights)[4].GetColor().ToVec3());

	shader->setUniform("pointLights[0].intensity", 1.0f);
	shader->setUniform("pointLights[1].intensity", 1.0f);
	shader->setUniform("pointLights[2].intensity", 1.0f);
	shader->setUniform("pointLights[3].intensity", 1.0f);
	shader->setUniform("pointLights[4].intensity", 1.0f);
	
	mesh->Draw(shader);

}