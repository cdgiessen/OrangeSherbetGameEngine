#include "OrangeSherbetGameEngine.h"
#include <iostream>

#include "Shader.h"

namespace Osge {

	OrangeSherbetGameEngine::OrangeSherbetGameEngine()
	{
		std::cout << "Starting up the Orange Sherbet Game Engine, Version idgaf" << std::endl;
	}


	OrangeSherbetGameEngine::~OrangeSherbetGameEngine()
	{
	}

	int OrangeSherbetGameEngine::StartUp(GLFWwindow *window) {
		setup_window(window);

		inputManager = new Osge::InputManager(window);
		inputManager->SetUp();

		return 0;
	}

	int OrangeSherbetGameEngine::ShutDown() {
		return 0;
	}


	void OrangeSherbetGameEngine::setup_window(GLFWwindow *window) {
		std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl; //for now use a version thats going to work regardless

																	   // Init GLFW
		if (!glfwInit())
			exit(EXIT_FAILURE);
		// Set all the required options for GLFW
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
		glfwWindowHint(GLFW_SAMPLES, 4);


		// Create a GLFWwindow object that we can use for GLFW's functions
		window = glfwCreateWindow(WIDTH, HEIGHT, "Oragne Sherbet Game Engine", nullptr, nullptr);
		if (!window)
		{
			glfwTerminate();
			exit(EXIT_FAILURE);
		}
		glfwMakeContextCurrent(window);

		// Set the required callback functions
		//glfwSetWindowSizeCallback(window, window_size_callback);
	
		//glfwSetKeyCallback(window, key_callback);
		//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		//glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)OnMouseButton);
		//glfwSetCursorPosCallback(window, OnMouseMoved);
		
		//glfwSetScrollCallback(window, OnScrollMoved);

		// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
		glewExperimental = GL_TRUE;

		glfwSwapInterval(1);

		// Initialize GLEW to setup the OpenGL Function pointers
		glewInit();

		
	}
}