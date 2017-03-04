#include "OrangeSherbetGameEngine.h"
#include <iostream>

namespace Osge {

	OrangeSherbetGameEngine::OrangeSherbetGameEngine()
	{
	}


	OrangeSherbetGameEngine::~OrangeSherbetGameEngine()
	{
	}

	int OrangeSherbetGameEngine::StartUp() {
		std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl; //for now use a version thats going to work regardless
																	   // Init GLFW
		glfwInit();
		// Set all the required options for GLFW
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		// Create a GLFWwindow object that we can use for GLFW's functions
		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
		if (window == nullptr)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);
	}

	int OrangeSherbetGameEngine::ShutDown() {

	}
}