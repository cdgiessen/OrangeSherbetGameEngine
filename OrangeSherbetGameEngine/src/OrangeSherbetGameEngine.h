#pragma once

#ifndef ORANGE_SHERBET_GAME_ENGINE_H
#define ORANGE_SHERBET_GAME_ENGINE_H


#define GLEW_STATIC
#include <GL\glew.h>
//#include <GL\GL.h>
//#include <GL\GLU.h>

#include <GLFW\glfw3.h>

#include "Window.h"
#include "InputManager.h"
#include "Scene.h"
#include "Shader.h"
#include "GLSLProgram.h"
#include "Camera.h"
#include "Mesh.h"
#include "Time.h"
#include "GameObject.h"

//#include "MeshPrimitives.h"

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
		
		void ProcessInputs();

		Window *window;
		InputManager *inputManager;
		Scene *scene;
	
		//All the subsystems
		//Memory Manager (pool, stack, etc)
		//File System(resource loading and save state loading)

		//Rendering/animation/texture graphics	
		//Physics manager
	};





#endif // !ORANGE_SHERBET_GAME_ENGINE_H

