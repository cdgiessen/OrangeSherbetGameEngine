#include "OrangeSherbetGameEngine.h"
#include <iostream>

#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Shader.h"
#include "Camera.h"
#include "MeshPrimitives.h"
#include "Mesh.h"

#include "CML\cml.h"

// Default Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

GLFWwindow *window;

//void OnMouseButton(GLFWwindow* window, int glfwButton, int glfwAction);

GLuint VAO, VBO, EBO;
GLuint triangleVBO, triangleVAO;

Camera camera(cml::vec3f(-3, 0, 0));

void setup_vao() {
	// Set up vertex data (and buffer(s)) and attribute pointers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 8 * 36 * sizeof(GLfloat), MeshPrimitives::cube, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Normal attribute								

	//Texture UV coordinate
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
}

// Is called whenever a key is pressed/released via GLFW
void OrangeSherbetGameEngine::TempKeyboardInput()
{
	float deltaTime = 0.05f;

	// Camera controls
	if (inputManager->GetKey(GLFW_KEY_W))
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (inputManager->GetKey(GLFW_KEY_S))
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (inputManager->GetKey(GLFW_KEY_A))
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (inputManager->GetKey(GLFW_KEY_D))
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (inputManager->GetKey(GLFW_KEY_Q))
		camera.ProcessKeyboard(DOWN, deltaTime);
	if (inputManager->GetKey(GLFW_KEY_E))
		camera.ProcessKeyboard(UP, deltaTime);
}

void OrangeSherbetGameEngine::TempMouseMove()
{
	camera.ProcessMouseMovement(inputManager->GetMouseOffsetPositionX(), inputManager->GetMouseOffsetPositionY());
	inputManager->ResetMouseOffset();
	std::cout << "xoff " << inputManager->GetMouseOffsetPositionX() << " yoff " << inputManager->GetMouseOffsetPositionY() << std::endl;
}

void OrangeSherbetGameEngine::TempMouseButton(){ //GLFWwindow* window, int glfwButton, int glfwAction) {
	//mouseHeldDown = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	if (glfwGetMouseButton(window->getGLFWWindow(), GLFW_MOUSE_BUTTON_LEFT))
		std::cout << "Left Clicked" << std::endl;
}



OrangeSherbetGameEngine::OrangeSherbetGameEngine()
{
	std::cout << "Starting up the Orange Sherbet Game Engine, Version idgaf" << std::endl;
}


OrangeSherbetGameEngine::~OrangeSherbetGameEngine()
{
}

int OrangeSherbetGameEngine::StartUp() {
	window = new Window(WIDTH, HEIGHT, false, "OGSE");

	inputManager = new InputManager(window->getGLFWWindow());



	return 0;
}

int OrangeSherbetGameEngine::ShutDown() {
	delete(inputManager);

	delete(window);

	std::cout << "Bye bye!" << std::endl; //y u ! werk?
	return 0;
}

void OrangeSherbetGameEngine::TempRun() {
	/*std::vector<Osge::Vertex> cubeVerticies;
	int pos = 0;
	for (int i = 0; i < 36; i++) {
		cubeVerticies.push_back(Osge::Vertex(
			cml::vec3f(MeshPrimitives::cube[pos++], MeshPrimitives::cube[pos++], MeshPrimitives::cube[pos++]),
			cml::vec3f(MeshPrimitives::cube[pos++], MeshPrimitives::cube[pos++], MeshPrimitives::cube[pos++]),
			cml::vec2f(MeshPrimitives::cube[pos++], MeshPrimitives::cube[pos++])));
	}*/

	Shader defaultShader("DefaultVertexShader.glsl", "DefaultFragmentShader.glsl");

	Texture cubeTexture("SolidColorCube.png", 96, 64);

	setup_vao();

	float timeish = 0;

	// Main Game loop
	while (!glfwWindowShouldClose(window->getGLFWWindow()))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		TempKeyboardInput();
		TempMouseMove();
		
		// Render
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //Set the background to a nice muted green
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Clear the colorbuffer

		// Draw the triangle
		defaultShader.Use();
		
		glActiveTexture(GL_TEXTURE0);
		cubeTexture.Bind();
		glUniform1i(glGetUniformLocation(defaultShader.Program, "myTexture"), 0);


		cml::mat4f view = camera.GetViewMatrix();
		//cml::mat4f projection = cml::mat4f::createPerspective(cml::degToRad(camera.Zoom), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.01f, 1000.0f);
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.01f, 100000.0f);
		cml::mat4f model = cml::mat4f();

		//timeish += 0.05f;	//model.addScaleFactor(cml::vec3f(1, sin(timeish) + 2, sin(timeish) + 2));	//model.addTranslation(cml::vec3f(sin(timeish), 0, 0));

		GLint modelLoc = glGetUniformLocation(defaultShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(defaultShader.Program, "view");
		GLint projLoc = glGetUniformLocation(defaultShader.Program, "projection");


		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, cml::mat4f::value_ptr(model));
		//glUniformMatrix4fv(projLoc, 1, GL_FALSE, cml::mat4f::value_ptr(projection));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, cml::mat4f::value_ptr(view));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		//std::cout << "Camera position = " << camera.Position << "Camera Lookint at position = " << camera.Front <<std::endl;

		// Swap the screen buffers
		glfwSwapBuffers(window->getGLFWWindow());
	}

	glDeleteBuffers(1, &VBO);
}
