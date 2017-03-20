#pragma once

#ifndef ORANGE_SHERBET_GAME_ENGINE_H
#define ORANGE_SHERBET_GAME_ENGINE_H


#define GLEW_STATIC
#include <gl/glew.h>

#include <GLFW\glfw3.h>

#include "Window.h"
#include "InputManager.h"

class OrangeSherbetGameEngine
	{
	public:
		OrangeSherbetGameEngine();
		~OrangeSherbetGameEngine();

		int StartUp();

		int ShutDown();

		//void setup_window();

		void TempRun();
		void TempKeyboardInput();
		void TempMouseMove();
		void TempMouseButton();

		Window *window;
		InputManager *inputManager;
	
		//All the subsystems
		//Memory Manager (pool, stack, etc)
		//File System(resource loading and save state loading)

		//Rendering/animation/texture graphics	
		//Physics manager

	
	};





#endif // !ORANGE_SHERBET_GAME_ENGINE_H

