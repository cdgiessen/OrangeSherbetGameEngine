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

	for (int i = 0; i < listOfLights->size(); i++) {
		(*listOfLights)[i]->FillUniform(shader, transform->GetViewMatrix());
	}

	mesh->Draw(shader);

}