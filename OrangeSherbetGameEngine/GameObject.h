#pragma once

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

//#include <glm\glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>

#include "CML\cml.h"
#include "Transform.h"
#include "Mesh.h"
#include "Shader.h"

class GameObject
{
public:
	GameObject(Transform *transform, Mesh *mesh, Shader *shader);
	~GameObject();

	void Draw(cml::mat4f newViewMatrix);

	Transform* transform;
private:
	Shader* shader;
	Mesh* mesh;
};

#endif // !GAME_OBJECT_H
