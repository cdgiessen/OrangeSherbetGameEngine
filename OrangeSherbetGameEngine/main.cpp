
#include <iostream>
#include "CML\cml.h"

#include <cstdlib> //for rand()
#include <chrono> //for timer

#include <vector>

#include <GLFW\glfw3.h>

#include "OrangeSherbetGameEngine.h"

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

typedef std::chrono::high_resolution_clock Clock; //gets me a timer

int main() {
	std::cout << "Starting up the Orange Sherbet Game Engine, Version 0.0.1" << std::endl;
	
	Osge::OrangeSherbetGameEngine gameEngine();


	std::cout << "Begin vertex tests" << std::endl << std::endl;
	const int vecTestSize = 5000;
	cml::vec3f vectors[vecTestSize];

	auto rotMatrix = cml::mat4f::createRotationMatrix(15.0, 25.0, 180.0);
	auto transMatrix = cml::mat4f::createTranslationMatrix( cml::vec3f(10.0, -4.0, 25.0));
	auto scaleMatrix = cml::mat4f::createTranslationMatrix(cml::vec3f(0.12, 3.1, 2.5));
	auto tranformationMatrix = rotMatrix * transMatrix * scaleMatrix;

	for (int i = 0; i < vecTestSize; i++)
	{
		vectors[i] = cml::vec3f(rand() % 200 - 100, rand() % 200 - 100, rand() % 200 - 100);
		//std::cout << vectors[i] << std::endl;
	}

	std::cout << "Multiplying vectors by rotation matrix (15, 25, 180)" << std::endl;

	auto beginCount = Clock::now();
	for (int i = 0; i < vecTestSize; i++)
	{
		//tranformationMatrix.addScaleFactor(5);
		tranformationMatrix.addTranslation(cml::vec3f(5, 5, 5));
		vectors[i] = tranformationMatrix * vectors[i];
	}
	auto endCount = Clock::now();

	std::cout << "Time taken to compute " << vecTestSize << " vector multiplications is " << std::chrono::duration_cast<std::chrono::nanoseconds>(endCount - beginCount).count() << " nanoseconds" << std::endl;
	std::cout << "Time taken to compute " << vecTestSize << " vector multiplications is " << std::chrono::duration_cast<std::chrono::microseconds>(endCount - beginCount).count() << " microseconds" << std::endl;

	const int nrows = 100;
	const int ncols = 100;
	
	std::vector<float> terVerts;
	terVerts.resize(5 * ncols * nrows);
	int curPlace = 0;
	int data[nrows][ncols];

	for (int i = 0; i < nrows; i++) {
		for (int j = 0; j < ncols; j++) {
			data[i][j] = rand() % 100;
		}
	}

	beginCount = Clock::now();
	//subdiv verts
	for (int i = 0; i < nrows - 1; i++) {
		for (int j = 0; j < ncols - 1; j++) {
			terVerts[curPlace++] = 0.5 + i - nrows / 2;
			terVerts[curPlace++] = ((data[i][j] + data[i][j + 1] + data[i + 1][j] + data[i + 1][j + 1]) / 4);
			terVerts[curPlace++] = 0.5 + j - ncols / 2;

			terVerts[curPlace++] = 0.25*(i + 0.5f); //uv coord
			terVerts[curPlace++] = 0.25*(j + 0.5f); //uv coord
		}
	}
	endCount = Clock::now();

	std::cout << "Time taken to calculate " << nrows * ncols << " vertices is " << std::chrono::duration_cast<std::chrono::nanoseconds>(endCount - beginCount).count() << " nanoseconds" << std::endl;
	std::cout << "Time taken to calculate " << nrows * ncols << " vertices is " << std::chrono::duration_cast<std::chrono::microseconds>(endCount - beginCount).count() << " microseconds" << std::endl;

	//std::cout << "Press any key to continue..." << std::endl;
	//std::getchar();

	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
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
	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);



	// Define the viewport dimensions
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Swap the screen buffers
		glfwSwapBuffers(window);
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