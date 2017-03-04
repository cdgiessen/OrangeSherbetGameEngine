#pragma once

#include "InputManager.h"
#include <GLFW\glfw3.h>

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

