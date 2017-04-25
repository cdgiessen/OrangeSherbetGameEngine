#pragma once

#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <glm/mat4x4.hpp>

#include "GameObject.h"
#include "Light.h"

class Scene
{
public:
	Scene();
	~Scene();

	std::vector<Light *> GetListOfLights();

	void AddGameObject(GameObject* obj);
	void AddLight(Light *light);
	
	void DrawScene(glm::mat4 view);

	void UpdateProjectionMatrix(glm::mat4 proj);

private:
	std::vector<Light *> lightsInScene;
	std::vector<GameObject> gameObjectsInScene;

	int maxNumPointLights = 5;
	int numPointLights = 0;

	int maxNumDirLights = 5;
	int numDirLights = 0;

	int maxNumSpotLights = 5;
	int numSpotLights = 0;
};

#endif SCENE_H