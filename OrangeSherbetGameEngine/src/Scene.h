#pragma once

#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "GameObject.h"

class Scene
{
public:
	Scene();
	~Scene();

	void AddGameObject(GameObject* obj);

private:
	std::vector<GameObject> GameObjectsInScene;


};

#endif SCENE_H