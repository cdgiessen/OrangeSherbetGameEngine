#include "GameObject.h"

#include <glm/gtc/type_ptr.hpp>

GameObject::GameObject(Transform *transform, Mesh *mesh, GLSLProgram *shader) : transform(transform), mesh(mesh), shader(shader)
{
}



GameObject::~GameObject()
{
}

void GameObject::Draw(glm::mat4 newViewMatrix, std::vector<Light* > *listOfLights) {

	shader->use();

	transform->SetViewMatrix(newViewMatrix);
	//Attempt at filling in blobs in the shader. Unsuccessful atm
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

	shader->setUniform("model", (transform->GetMatrix()));
	shader->setUniform("view", (transform->GetViewMatrix()));
	shader->setUniform("proj", (transform->GetProjectionMatrix()));

	shader->setUniform("normalMat", glm::transpose(glm::inverse( glm::mat3(transform->GetViewMatrix()*transform->GetMatrix()) )) );

	//for (int i = 0; i < listOfLights->size(); i++) {
	//	(*listOfLights)[i].FillUniform(shader, i, eyespace);
	//}

	shader->setUniform("pointLights[0].position", transform->GetViewMatrix() * glm::vec4((*listOfLights)[0]->GetPosition(), 1.0f));
	shader->setUniform("pointLights[1].position", transform->GetViewMatrix() * glm::vec4((*listOfLights)[1]->GetPosition(), 1.0f));
	shader->setUniform("pointLights[2].position", transform->GetViewMatrix() * glm::vec4((*listOfLights)[2]->GetPosition(), 1.0f));
	shader->setUniform("pointLights[3].position", transform->GetViewMatrix() * glm::vec4((*listOfLights)[3]->GetPosition(), 1.0f));
	shader->setUniform("pointLights[4].position", transform->GetViewMatrix() * glm::vec4((*listOfLights)[4]->GetPosition(), 1.0f));

	shader->setUniform("pointLights[0].color", (*listOfLights)[0]->GetColor().ToVec3());
	shader->setUniform("pointLights[1].color", (*listOfLights)[1]->GetColor().ToVec3());
	shader->setUniform("pointLights[2].color", (*listOfLights)[2]->GetColor().ToVec3());
	shader->setUniform("pointLights[3].color", (*listOfLights)[3]->GetColor().ToVec3());
	shader->setUniform("pointLights[4].color", (*listOfLights)[4]->GetColor().ToVec3());

	shader->setUniform("pointLights[0].intensity", (*listOfLights)[0]->GetIntensity());
	shader->setUniform("pointLights[1].intensity", (*listOfLights)[1]->GetIntensity());
	shader->setUniform("pointLights[2].intensity", (*listOfLights)[2]->GetIntensity());
	shader->setUniform("pointLights[3].intensity", (*listOfLights)[3]->GetIntensity());
	shader->setUniform("pointLights[4].intensity", (*listOfLights)[4]->GetIntensity());

	//Direction light
	shader->setUniform("dirlights[0].direction", glm::vec3(transform->GetViewMatrix() * glm::vec4((*listOfLights)[5]->GetDirection(), 1.0f)));
	shader->setUniform("dirlights[0].color", (*listOfLights)[5]->GetColor().ToVec3());
	shader->setUniform("dirlights[0].intensity", (*listOfLights)[5]->GetIntensity());
	
	mesh->Draw(shader);

}