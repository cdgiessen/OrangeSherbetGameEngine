#pragma once

#ifndef ORANGE_SHERBET_GAME_ENGINE_H
#define ORANGE_SHERBET_GAME_ENGINE_H

#define GLEW_STATIC
#include <gl/glew.h>

#include <GLFW\glfw3.h>

#include "InputManager.h"

// Default Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;


namespace Osge {

	class OrangeSherbetGameEngine
	{
	public:
		OrangeSherbetGameEngine();
		~OrangeSherbetGameEngine();

		int StartUp(GLFWwindow *window);

		int ShutDown();

		void setup_window(GLFWwindow *window);

		InputManager *inputManager;
	
		//All the subsystems
		//Memory Manager (pool, stack, etc)
		//File System(resource loading and save state loading)

		//Rendering/animation/texture graphics	
		//Physics manager

	
	};

}



#endif // !ORANGE_SHERBET_GAME_ENGINE_H

