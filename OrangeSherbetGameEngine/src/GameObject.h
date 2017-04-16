#pragma once

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <vector>

#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#include "CML\cml.h"
#include "Transform.h"
#include "Mesh.h"
#include "Shader.h"
#include "GLSLProgram.h"
#include "Light.h"

class GameObject
{
public:
	GameObject(Transform *transform, Mesh *mesh, GLSLProgram *shader);
	~GameObject();

	void Draw(glm::mat4 newViewMatrix, std::vector<Light>* listOfLights);

	Transform* transform;
	
private:
	GLSLProgram* shader;
	Mesh* mesh;
};

#endif // !GAME_OBJECT_H
