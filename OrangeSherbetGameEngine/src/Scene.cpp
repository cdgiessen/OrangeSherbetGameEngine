#include "Scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::AddGameObject(GameObject *obj) {
	gameObjectsInScene.push_back(*obj);
}

void Scene::AddLight(Light *light) {
	lightsInScene.push_back(*light);
}

void Scene::DrawScene(glm::mat4 view) {
	for(GameObject &obj : gameObjectsInScene) {
		obj.Draw(view);
	}
}

void Scene::UpdateProjectionMatrix(glm::mat4 proj) {
	for (GameObject &obj : gameObjectsInScene) {
		obj.transform->SetProjectionMatrix(proj);
	}
}

