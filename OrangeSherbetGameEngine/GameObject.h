#pragma once

#ifndef GAME_OBJECT_H

#include "CML\cml.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

private:
	cml::vec3f position;
};

#endif // !GAME_OBJECT_H
