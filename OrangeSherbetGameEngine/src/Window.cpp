#include "Window.h"

#include <iostream>


Window::Window(int width, int height, bool fullscreen, char *title) : width(width), height(height), fullscreen(false)
{
	std::cout << "Creating window..." << std::endl;
	std::cout << "Starting GLFW context, OpenGL 4.0" << std::endl; //for now use a version thats going to work regardless

	if (!glfwInit())    // Init GLFW
		exit(EXIT_FAILURE);
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 4);


	// Create a GLFWwindow object that we can use for GLFW's functions
	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!window)
	{
		fprintf(stderr, "ERROR: GLFW Could Not Open Window"); // TODO: Print this to log file
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Make the current context be the window that was just created

	glfwSetWindowSizeCallback(window, window_size_callback); // Set the required callback functions

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Set mouse mode to be captured

	glfwSetCursorPos(window, 0, 0); // Set mouse position to center

	glfwSwapInterval(1);

	// Define the viewport dimensions
	if (window == NULL) {
		std::cout << "SHITS ON FIRE YO" << std::endl;
	}
	glfwGetFramebufferSize(window, &width, &height);
	
	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;

	// Initialize GLEW to setup the OpenGL Function pointers
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "Error initializing GLEW: %s\n", glewGetErrorString(err));
	}
	
	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
}


Window::~Window()
{
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwDestroyWindow(getGLFWWindow());
	glfwTerminate();
	std::cout << "Window and with it the GLFW context terminated" << std::endl;
}

GLFWwindow *Window::getGLFWWindow()
{
	return window;
}

int Window::getHeight()
{
	return height;
}

int Window::getWidth()
{
	return width;
}

bool Window::isFullscreen()
{
	return fullscreen;
}

bool Window::isClosed()
{
	return shouldClose;
}

void Window::close()
{
	glfwWindowShouldClose(window);
	shouldClose = true;
}

void Window::window_size_callback(GLFWwindow *window, int newWidth, int newHeight)
{
	glViewport(0, 0, newWidth, newHeight); 	// Change glViewport to new window size

	//myWindow->projectionMatrix = cml::mat4f::createPerspective(90.0f, float(newWidth / newHeight), 0.001f, 1000.0f);
}

