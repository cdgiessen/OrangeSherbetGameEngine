#include "Scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{
}

std::vector<Light *> Scene::GetListOfLights() {
	return lightsInScene;
}

void Scene::AddGameObject(GameObject *obj) {
	gameObjectsInScene.push_back(*obj);
}

void Scene::AddLight(Light *light) {
	switch (light->GetLightType())
	{
	case (Light::LightType::Point):
		if (numPointLights < maxNumPointLights) {
			numPointLights++;
			light->SetLightIndex(numPointLights - 1);
			lightsInScene.push_back(light);
		}
		break;
	case(Light::LightType::Dir):
		if (numDirLights < maxNumDirLights) {
			numDirLights++;
			light->SetLightIndex(numDirLights - 1);
			lightsInScene.push_back(light);
		}
		break;
	case(Light::LightType::Spot):
		if (numSpotLights < maxNumSpotLights) {
			numSpotLights++;
			light->SetLightIndex(numSpotLights - 1);
			lightsInScene.push_back(light);
		}
		break;
	}
}

void Scene::DrawScene(glm::mat4 view) {
	for(GameObject &obj : gameObjectsInScene) {
		obj.Draw(view, &lightsInScene);
	}
}

void Scene::UpdateProjectionMatrix(glm::mat4 proj) {
	for (GameObject &obj : gameObjectsInScene) {
		obj.transform->SetProjectionMatrix(proj);
	}
}

