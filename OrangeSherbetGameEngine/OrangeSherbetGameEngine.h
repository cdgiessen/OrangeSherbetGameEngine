#pragma once

#ifndef ORANGE_SHERBET_GAME_ENGINE_H


#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW\glfw3.h>

#include "InputManager.h"



namespace Osge {

	class OrangeSherbetGameEngine
	{
	public:
		OrangeSherbetGameEngine();
		~OrangeSherbetGameEngine();

		int StartUp();

		int ShutDown();


	
		//All the subsystems
		//Memory Manager (pool, stack, etc)
		//File System(resource loading and save state loading)

		//Rendering/animation/texture graphics	
		//Physics manager

		GLFWwindow *window;

		InputManager *inputManager;
	};

}

#endif // !ORANGE_SHERBET_GAME_ENGINE_H

