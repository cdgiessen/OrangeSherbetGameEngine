
#include <iostream>
#include "CML\cml.h"

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW\glfw3.h>

#include "OrangeSherbetGameEngine.h"

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;


int main() {
	std::cout << "Starting up the Orange Sherbet Game Engine, Version idgaf" << std::endl;

	Osge::OrangeSherbetGameEngine * gameEngine = new Osge::OrangeSherbetGameEngine();

	gameEngine->StartUp();

	// Set the required callback functions
	glfwSetKeyCallback(gameEngine->window, key_callback);



	// Define the viewport dimensions
	int width, height;
	glfwGetFramebufferSize(gameEngine->window, &width, &height);
	glViewport(0, 0, width, height);

	// Game loop
	while (!glfwWindowShouldClose(gameEngine->window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Swap the screen buffers
		glfwSwapBuffers(gameEngine->window);
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	std::cout << key << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}