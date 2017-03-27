#include "OrangeSherbetGameEngine.h"
#include <iostream>

#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "CML\cml.h"
#include "CML\mat4.h"

#include "MeshPrimitives.h"

// Default Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

GLFWwindow *window;

//void OnMouseButton(GLFWwindow* window, int glfwButton, int glfwAction);

GLuint VAO, VBO, EBO;
GLuint triangleVBO, triangleVAO;

Camera camera(cml::vec3f(-3, 0, 0));

glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.01f, 100000.0f);

Shader* defaultShader;
Texture* cubeTexture;
Mesh* cubeMesh;
Mesh* quadMesh;

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
	//std::cout << "xoff " << inputManager->GetMouseOffsetPositionX() << " yoff " << inputManager->GetMouseOffsetPositionY() << std::endl;
}

void OrangeSherbetGameEngine::TempMouseButton() { //GLFWwindow* window, int glfwButton, int glfwAction) {
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
	std::vector<Vertex> cubeVerticies;

	//Left face
	cubeVerticies.push_back(Vertex(cml::vec3f(0.5f, -0.5f, -0.5f),  cml::vec3f(0.0f, 0.0f, -1.0f), cml::vec2f(0.333f, 1.0f)));
	cubeVerticies.push_back(Vertex(cml::vec3f(-0.5f, -0.5f, -0.5f), cml::vec3f(0.0f, 0.0f, -1.0f), cml::vec2f(0.667f, 1.0f)));
	cubeVerticies.push_back(Vertex(cml::vec3f(0.5f, 0.5f, -0.5f),   cml::vec3f(0.0f, 0.0f, -1.0f), cml::vec2f(0.333f, 0.5f)));
	cubeVerticies.push_back(Vertex(cml::vec3f(-0.5f, 0.5f, -0.5f),  cml::vec3f(0.0f, 0.0f, -1.0f), cml::vec2f(0.667f, 0.5f)));
	cubeVerticies.push_back(Vertex(cml::vec3f(0.5f, 0.5f, -0.5f),   cml::vec3f(0.0f, 0.0f, -1.0f), cml::vec2f(0.333f, 0.5f)));
	cubeVerticies.push_back(Vertex(cml::vec3f(-0.5f, -0.5f, -0.5f), cml::vec3f(0.0f, 0.0f, -1.0f), cml::vec2f(0.667f, 1.0f)));

	//Right face
	cubeVerticies.push_back(Vertex(cml::vec3f(-0.5f, -0.5f, 0.5f), cml::vec3f(0.0f, 0.0f, 1.0f), cml::vec2f(0.333f, 0.5f)));
	cubeVerticies.push_back(Vertex(cml::vec3f(0.5f, -0.5f, 0.5f),  cml::vec3f(0.0f, 0.0f, 1.0f), cml::vec2f(0.667f, 0.5f)));
	cubeVerticies.push_back(Vertex(cml::vec3f(0.5f, 0.5f, 0.5f),   cml::vec3f(0.0f, 0.0f, 1.0f), cml::vec2f(0.667f, 0.0f)));
	cubeVerticies.push_back(Vertex(cml::vec3f(0.5f, 0.5f, 0.5f),   cml::vec3f(0.0f, 0.0f, 1.0f), cml::vec2f(0.667f, 0.0f)));
	cubeVerticies.push_back(Vertex(cml::vec3f(-0.5f, 0.5f, 0.5f),  cml::vec3f(0.0f, 0.0f, 1.0f), cml::vec2f(0.333f, 0.0f)));
	cubeVerticies.push_back(Vertex(cml::vec3f(-0.5f, -0.5f, 0.5f), cml::vec3f(0.0f, 0.0f, 1.0f), cml::vec2f(0.333f, 0.5f)));

	//Back face																											
	cubeVerticies.push_back(Vertex(cml::vec3f(-0.5f, -0.5f, 0.5f),  cml::vec3f(-1.0f, 0.0f, 0.0f), cml::vec2f(0.333f, 1.0f)));
	cubeVerticies.push_back(Vertex(cml::vec3f(-0.5f, 0.5f, 0.5f),   cml::vec3f(-1.0f, 0.0f, 0.0f), cml::vec2f(0.333f, 0.5f)));
	cubeVerticies.push_back(Vertex(cml::vec3f(-0.5f, -0.5f, -0.5f), cml::vec3f(-1.0f, 0.0f, 0.0f), cml::vec2f(0.0f, 1.0f)));
	cubeVerticies.push_back(Vertex(cml::vec3f(-0.5f, 0.5f, 0.5f),   cml::vec3f(-1.0f, 0.0f, 0.0f), cml::vec2f(0.333f, 0.5f)));
	cubeVerticies.push_back(Vertex(cml::vec3f(-0.5f, 0.5f, -0.5f),  cml::vec3f(-1.0f, 0.0f, 0.0f), cml::vec2f(0.0f, 0.5f)));
	cubeVerticies.push_back(Vertex(cml::vec3f(-0.5f, -0.5f, -0.5f), cml::vec3f(-1.0f, 0.0f, 0.0f), cml::vec2f(0.0f, 1.0f)));

	//Front face																										
	cubeVerticies.push_back(Vertex(cml::vec3f(0.5f, 0.5f, -0.5f),  cml::vec3f(1.0f, 0.0f, 0.0f), cml::vec2f(0.334f, 0.0f)));
	cubeVerticies.push_back(Vertex(cml::vec3f(0.5f, 0.5f, 0.5f),   cml::vec3f(1.0f, 0.0f, 0.0f), cml::vec2f(0.0f, 0.0f)));
	cubeVerticies.push_back(Vertex(cml::vec3f(0.5f, -0.5f, -0.5f), cml::vec3f(1.0f, 0.0f, 0.0f), cml::vec2f(0.334f, 0.5f)));
	cubeVerticies.push_back(Vertex(cml::vec3f(0.5f, -0.5f, 0.5f),  cml::vec3f(1.0f, 0.0f, 0.0f), cml::vec2f(0.0f, 0.5f)));
	cubeVerticies.push_back(Vertex(cml::vec3f(0.5f, -0.5f, -0.5f), cml::vec3f(1.0f, 0.0f, 0.0f), cml::vec2f(0.334f, 0.5f)));
	cubeVerticies.push_back(Vertex(cml::vec3f(0.5f, 0.5f, 0.5f),   cml::vec3f(1.0f, 0.0f, 0.0f), cml::vec2f(0.0f, 0.0f)));

	//Bottom face
	cubeVerticies.push_back(Vertex(cml::vec3f(-0.5f, -0.5f, -0.5f), cml::vec3f(0.0f, -1.0f, 0.0f), cml::vec2f(1.0f, 1.0f)));
	cubeVerticies.push_back(Vertex(cml::vec3f(0.5f, -0.5f, -0.5f),  cml::vec3f(0.0f, -1.0f, 0.0f), cml::vec2f(0.667f, 1.0f)));
	cubeVerticies.push_back(Vertex(cml::vec3f(0.5f, -0.5f, 0.5f),   cml::vec3f(0.0f, -1.0f, 0.0f), cml::vec2f(0.667f, 0.5f)));
	cubeVerticies.push_back(Vertex(cml::vec3f(0.5f, -0.5f, 0.5f),   cml::vec3f(0.0f, -1.0f, 0.0f), cml::vec2f(0.667f, 0.5f)));
	cubeVerticies.push_back(Vertex(cml::vec3f(-0.5f, -0.5f, 0.5f),  cml::vec3f(0.0f, -1.0f, 0.0f), cml::vec2f(1.0f, 0.5f)));
	cubeVerticies.push_back(Vertex(cml::vec3f(-0.5f, -0.5f, -0.5f), cml::vec3f(0.0f, -1.0f, 0.0f), cml::vec2f(1.0f, 1.0f)));

	//Top face
	cubeVerticies.push_back(Vertex(cml::vec3f(-0.5f, 0.5f, -0.5f), cml::vec3f(0.0f, 1.0f, 0.0f), cml::vec2f(0.667f, 0.5f)));
	cubeVerticies.push_back(Vertex(cml::vec3f(0.5f, 0.5f, 0.5f),   cml::vec3f(0.0f, 1.0f, 0.0f), cml::vec2f(1.0f, 0.0f)));
	cubeVerticies.push_back(Vertex(cml::vec3f(0.5f, 0.5f, -0.5f),  cml::vec3f(0.0f, 1.0f, 0.0f), cml::vec2f(1.0f, 0.5f)));
	cubeVerticies.push_back(Vertex(cml::vec3f(-0.5f, 0.5f, 0.5f),  cml::vec3f(0.0f, 1.0f, 0.0f), cml::vec2f(0.667f, 0.0f)));
	cubeVerticies.push_back(Vertex(cml::vec3f(0.5f, 0.5f, 0.5f),   cml::vec3f(0.0f, 1.0f, 0.0f), cml::vec2f(1.0f, 0.0f)));
	cubeVerticies.push_back(Vertex(cml::vec3f(-0.5f, 0.5f, -0.5f), cml::vec3f(0.0f, 1.0f, 0.0f), cml::vec2f(0.667f, 0.5f)));

	defaultShader = new Shader("DefaultVertexShader.glsl", "DefaultFragmentShader.glsl");
	cubeTexture = new Texture("SolidColorCube.png", 96, 64, (TextureType)0);
	cubeMesh = new Mesh(cubeVerticies, std::vector<Texture>{*cubeTexture});

	Transform cubeTransform[6]{ 
		Transform(camera.GetViewMatrix(), glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.01f, 10000.0f)),
		Transform(camera.GetViewMatrix(), glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.01f, 10000.0f)),
		Transform(camera.GetViewMatrix(), glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.01f, 10000.0f)),
		Transform(camera.GetViewMatrix(), glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.01f, 10000.0f)),
		Transform(camera.GetViewMatrix(), glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.01f, 10000.0f)),
		Transform(camera.GetViewMatrix(), glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.01f, 10000.0f)) };


	cml::mat4f model;
	model.setToTranslation(cml::vec3f(3, 0, 0));
	model.setScaleFactor(cml::vec3f(1, 1, 1));
	cubeTransform[0].SetModelMatrix(model);
	model.setScaleFactor(cml::vec3f(1, 1, 1));

	model.setToTranslation(cml::vec3f(0, 1, 0));
	cubeTransform[1].SetModelMatrix(model);

	model.setToTranslation(cml::vec3f(0, 2, 0));
	cubeTransform[2].SetModelMatrix(model);

	model.setToTranslation(cml::vec3f(0, 3, 0));
	cubeTransform[3].SetModelMatrix(model);

	model.rotate(cml::vec3f(0, 0, 1), 0);
	model.scale(cml::vec3f(1, 2, 1));
	model.translate(cml::vec3f(-4, 0, 0));
	cubeTransform[4].SetModelMatrix(model);

	model.setToTranslation(cml::vec3f(0, 0, 0));
	model.setScaleFactor(cml::vec3f(1, 1, 1));

	model.rotate(cml::vec3f(0, 0, 1), 3.14f/2.0f);
	model.scale(cml::vec3f(1, 2, 1));
	model.translate(cml::vec3f(-1, 0, 0));	

	cubeTransform[5].SetModelMatrix(model);

	GameObject cubeObject[6]{ GameObject(&cubeTransform[0], cubeMesh, defaultShader),
		GameObject(&cubeTransform[1], cubeMesh, defaultShader),
		GameObject(&cubeTransform[2], cubeMesh, defaultShader),
		GameObject(&cubeTransform[3], cubeMesh, defaultShader),
		GameObject(&cubeTransform[4], cubeMesh, defaultShader),
		GameObject(&cubeTransform[5], cubeMesh, defaultShader)
	};

	//setup_vao();

	float timeish = 0;

	// Main Game loop
	while (!glfwWindowShouldClose(window->getGLFWWindow()))
	{
		timeish += 0.016f;
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		TempKeyboardInput();
		TempMouseMove();

		// Render
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //Set the background to a nice muted green
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Clear the colorbuffer


		// Draw the triangle
		//DrawCube();

		cml::mat4f view = camera.GetViewMatrix();

		//RENDER
		for (int i = 0; i < 6; i++) {
			cml::mat4f model;
			model = cubeObject[i].transform->GetModelMatrix();
			cml::vec3f invscale = model.getScale();
			cml::vec3f scale = model.getScale();
			invscale.x = 1 / invscale.x;
			invscale.y = 1 / invscale.y;
			invscale.z = 1 / invscale.z;
			model.scale(invscale);
			model.rotate(cml::vec3f((0), (0), (1)), timeish);
			model.scale(scale);
			cubeObject[i].transform->SetModelMatrix(model);
			cubeObject[i].Draw(view);
		}

		//std::cout << "Camera position = " << camera.Position << "Camera Lookint at position = " << camera.Front <<std::endl;

		// Swap the screen buffers
		glfwSwapBuffers(window->getGLFWWindow());
	}

	glDeleteBuffers(1, &VBO);
}
