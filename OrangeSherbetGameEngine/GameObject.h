#pragma once

#ifndef GAME_OBJECT_H

#include "CML\cml.h"
#include "Transform.h"
class GameObject
{
public:
	GameObject();
	~GameObject();

private:
	Transform transform;
};

#endif // !GAME_OBJECT_H
