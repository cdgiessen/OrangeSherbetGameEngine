#include "OrangeSherbetGameEngine.h"
#include <iostream>
#include <unordered_map>

#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <noise/noise.h>

//#include "CML\cml.h"
//#include "CML\mat4.h"

// Default Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

GLFWwindow *window;

//void OnMouseButton(GLFWwindow* window, int glfwButton, int glfwAction);

//GLuint VAO, VBO, EBO;
//GLuint triangleVBO, triangleVAO;

Camera camera(glm::vec3(-3, 0, 0));
Time myTime;

glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.01f, 10000.0f);

Shader* defaultShader;
GLSLProgram* shader;
Mesh* cubeMesh;
Mesh* quadMesh;


OrangeSherbetGameEngine::OrangeSherbetGameEngine() {
	StartUp();
}


OrangeSherbetGameEngine::~OrangeSherbetGameEngine() {}

// Is called whenever a key is pressed/released via GLFW
void OrangeSherbetGameEngine::TempKeyboardInput()
{
	float deltaTime = myTime.GetDeltaTime();

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



int OrangeSherbetGameEngine::StartUp() {
	std::cout << "Starting up the Orange Sherbet Game Engine" << std::endl;
	
	window = new Window(WIDTH, HEIGHT, false, "OGSE");

	inputManager = new InputManager(window->getGLFWWindow());

	scene = new Scene();

	TempRun();

	return 0;
}

int OrangeSherbetGameEngine::ShutDown() {
	delete(inputManager);

	delete(window);

	std::cout << "Bye bye!" << std::endl;
	return 0;
}


void OrangeSherbetGameEngine::TempRun() {
	defaultShader = new Shader("Shaders/DefaultShader.vert", "Shaders/DefaultShader.frag");
	shader = new GLSLProgram();
	shader->compileShader("Shaders/DefaultShader.vert", GLSLShader::VERTEX);
	shader->compileShader("Shaders/DefaultShader.frag", GLSLShader::FRAGMENT);
	shader->link();

	camera.SetProjMatrix(projection);

	//cubeTexture = new Texture("Assets/Images/SolidColorCube.png", 96, 64, (TextureType)0);
	Texture* cubeTexture = new Texture("Assets/Models/Cube/albedo.png", 128, 128, (TextureType)0);
	Texture* specCubeTex = new Texture("Assets/Models/Cube/specular.png", 128, 128, (TextureType)1);

	Material* cMat = new Material(cubeTexture, specCubeTex);
	cMat->SetAmbient(glm::vec3(0.1, 0.1, 0.1));
	//cubeMesh = LoadMesh("Assets/Models/cube/cube.obj", cMat);
	cubeMesh = LoadCubeMesh(cMat);
	Transform cubeTransform[6]{ 
		Transform(camera.GetViewMatrix(), camera.GetProjMatrix()),
		Transform(camera.GetViewMatrix(), camera.GetProjMatrix()),
		Transform(camera.GetViewMatrix(), camera.GetProjMatrix()),
		Transform(camera.GetViewMatrix(), camera.GetProjMatrix()),
		Transform(camera.GetViewMatrix(), camera.GetProjMatrix()),
		Transform(camera.GetViewMatrix(), camera.GetProjMatrix()) };

	cubeTransform[0].SetLocalScale(glm::vec3(1, 1, 1.5));
	cubeTransform[2].SetLocalScale(glm::vec3(15, 1, 15));
	cubeTransform[2].SetLocalPosition(glm::vec3(0, -2, 0));

	GameObject cubeObject0(&cubeTransform[0], cubeMesh, shader);
	GameObject cubeObject1(&cubeTransform[1], cubeMesh, shader);
	GameObject cubeObject2(&cubeTransform[2], cubeMesh, shader);
	GameObject cubeObject3(&cubeTransform[3], cubeMesh, shader);
	GameObject cubeObject4(&cubeTransform[4], cubeMesh, shader);
	GameObject cubeObject5(&cubeTransform[5], cubeMesh, shader);
	
	scene->AddGameObject(&cubeObject0);
	scene->AddGameObject(&cubeObject1);
	scene->AddGameObject(&cubeObject2);
	scene->AddGameObject(&cubeObject3);
	scene->AddGameObject(&cubeObject4);
	scene->AddGameObject(&cubeObject5);

	Texture* teapotTexture = new Texture("Assets/Models/teapot/albedo.png", 128, 128, (TextureType)0);
	Material* tMat = new Material(teapotTexture);
	tMat->SetShininess(128.0f);
	tMat->SetSpecular(glm::vec3(0.8, 0.8, 0.8));
	Mesh* teapotMesh = LoadMeshNoNormals("Assets/Models/teapot/teapot.obj", tMat);
	Transform* teapotTransform = new Transform(camera.GetViewMatrix(), camera.GetProjMatrix());
	GameObject teapot(teapotTransform, teapotMesh, shader);

	scene->AddGameObject(&teapot);

	Texture* sibenikTexture = new Texture("Assets/Models/sibenik/kamen.png", 512, 512, (TextureType)0);
	Material* sMat = new Material(sibenikTexture);
	sMat->SetAmbient(glm::vec3(1, 1, 1));
	Mesh* sibenikMesh = LoadMesh("Assets/Models/sibenik/sibenik.obj", sMat);
	Transform* sibenikTransform = new Transform(camera.GetViewMatrix(), camera.GetProjMatrix());
	GameObject sibenik(sibenikTransform, sibenikMesh, shader);

	scene->AddGameObject(&sibenik);

	//cml::mat4f model;
	teapot.transform->SetLocalScale(glm::vec3(0.01f, 0.01f, 0.01f));
	//setup_vao();

	Light* l0 = new Light(Color(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.7f, Light::LightType::Point);
	Light* l1 = new Light(Color(1.0f, 0.0f, 0.0f), glm::vec3(4.0f, 2.0f, 4.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, Light::LightType::Point);
	Light* l2 = new Light(Color(0.0f, 0.0f, 1.0f), glm::vec3(-4.0f, 2.0f, 4.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, Light::LightType::Point);
	Light* l3 = new Light(Color(1.0f, 1.0f, 0.0f), glm::vec3(4.0f, 2.0f, -4.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, Light::LightType::Point);
	Light* l4 = new Light(Color(0.0f, 1.0f, 0.0f), glm::vec3(-4.0f, 2.0f, -4.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, Light::LightType::Point);
	
	scene->AddLight(l0);
	scene->AddLight(l1);
	scene->AddLight(l2);
	scene->AddLight(l3);
	scene->AddLight(l4);

	// Main Game loop
	while (!glfwWindowShouldClose(window->getGLFWWindow()))
	{
		if (inputManager->GetKey(70)) //speed up time. Literally.
		{
			myTime.Pause();	
		}
		else {
			myTime.UnPause();
		}

		myTime.TickClock();
		//myTime.PrintCurrentTime();

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		if (window->windowSizeChanged) {
			camera.SetProjMatrix(glm::perspective(glm::radians(camera.Zoom), (float)window->getWidth() / (float)window->getHeight(), 0.01f, 1000.0f));
			scene->UpdateProjectionMatrix(camera.GetProjMatrix());
			window->windowSizeChanged = false;
		}

		TempKeyboardInput();
		TempMouseMove();

		// Render
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //Set the background to a nice muted green
		//glClearColor(sin(myTime.GetCurrentTime()), 0.3f, 0.3f, 1.0f); //Set the background to a nice muted green
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Clear the colorbuffer


		// Draw the triangle
		//DrawCube();

		glm::mat4 view = camera.GetViewMatrix();

		//RENDER
		cubeObject0.transform->SetLocalRotation(0, myTime.GetCurrentTime(), 0);
		cubeObject1.transform->SetLocalRotation(270, myTime.GetCurrentTime(), 45);
		//cubeObject2.transform->SetLocalRotation(0, myTime.GetCurrentTime()/8, 0);
		//cubeObject2.transform->SetLocalPosition(glm::vec3(0.0f, 3.0f + sin(myTime.GetCurrentTime()*1.5f) * 1, 0));
		cubeObject3.transform->SetLocalRotation(45, myTime.GetCurrentTime()*1.5f, 0);
		cubeObject4.transform->SetLocalRotation(myTime.GetCurrentTime()*3.0f, myTime.GetCurrentTime()*1.667f , 0);
		cubeObject5.transform->SetLocalRotation(myTime.GetCurrentTime(), myTime.GetCurrentTime() *2, myTime.GetCurrentTime() /1.5f);

		cubeObject0.transform->SetLocalPosition(glm::vec3(4 + sin(myTime.GetCurrentTime() * 3 + 0.5) * 2, 0, - 2 + sin(myTime.GetCurrentTime() + 0.2) * 0.5f));
		cubeObject1.transform->SetLocalPosition(glm::vec3(-3, 0, 4 + sin(myTime.GetCurrentTime() * 2 + 1.54) * 3));
		//cubeObject2.transform->SetLocalPosition(glm::vec3(0, -3 + sin(myTime.GetCurrentTime() * 3) * 3, 0));
		cubeObject3.transform->SetLocalPosition(glm::vec3(-2, 4 + sin(myTime.GetCurrentTime() * 3) * 2, 1));
		cubeObject4.transform->SetLocalPosition(glm::vec3(2 + sin(myTime.GetCurrentTime()*5) * 2, 0, -4 + sin(myTime.GetCurrentTime() * 2 + 2) * 3));
		cubeObject5.transform->SetLocalPosition(glm::vec3(-4 + sin(myTime.GetCurrentTime()*3 + 1) * 2, 0, -2));
		
		teapot.transform->SetLocalRotation(0, myTime.GetCurrentTime()/4, 0);
		teapot.transform->SetLocalScale(0.01f, 0.01f*(1.5f + sin(myTime.GetCurrentTime())/3), 0.01f);

		//l0->SetPosition(glm::vec3(sin(myTime.GetCurrentTime())*5, 1, cos(myTime.GetCurrentTime())*5));
		//l1->SetPosition(glm::vec3(4.0f + sin(myTime.GetCurrentTime()*3.0f)*3.0f,	2.0f, 4.0f + cos(myTime.GetCurrentTime()*3.0f)*3.0f));
		//l2->SetPosition(glm::vec3(-4.0f + sin(myTime.GetCurrentTime()*3.0f)*3.0f,	2.0f, 4.0f + cos(-myTime.GetCurrentTime()*3.0f)*3.0f));
		//l3->SetPosition(glm::vec3(4.0f + sin(-myTime.GetCurrentTime()*3.0f)*3.0f,	2.0f, -4.0f + cos(myTime.GetCurrentTime()*3.0f)*3.0f));
		//l4->SetPosition(glm::vec3(-4.0f + sin(-myTime.GetCurrentTime()*3.0f)*3.0f,	2.0f, -4.0f + cos(-myTime.GetCurrentTime()*3.0f)*3.0f));
		
		scene->DrawScene(view);

		//std::cout << "Camera position = " << camera.Position << "Camera Lookint at position = " << camera.Front <<std::endl;

		// Swap the screen buffers
		glfwSwapBuffers(window->getGLFWWindow());
	}

	ShutDown();
}
