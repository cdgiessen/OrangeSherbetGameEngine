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
const GLuint WIDTH = 1600, HEIGHT = 900;

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

nlohmann::json OrangeSherbetGameEngine::LoadSettings() {
	// read the settings file. Needs to do error checking if it isn't present, then load defaults.
	std::ifstream input_settings("settings.json");
	nlohmann::json json_settings;
	input_settings >> json_settings;

	std::cout << std::setw(4) << json_settings << std::endl;

	int screenWidth = json_settings["screen_dimentions"]["screen_width"];
	int screenHeight = json_settings["screen_dimentions"]["screen_height"];
	if (screenWidth <= 0)
		json_settings["screen_dimentions"]["screen_width"] = 800;
	if (screenHeight <= 0)
		json_settings["screen_dimentions"]["screen_height"] = 600;

	return json_settings;
}

int OrangeSherbetGameEngine::StartUp() {
	std::cout << "Starting up the Orange Sherbet Game Engine" << std::endl;

	nlohmann::json settings = LoadSettings();

	window = new Window(settings["screen_dimentions"]["screen_width"], settings["screen_dimentions"]["screen_height"], false, "OGSE");

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


void OrangeSherbetGameEngine::ProcessInputs() {
	// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
	glfwPollEvents();

	if (inputManager->GetKey(340)) { //speed up camera movement.
		camera.MovementSpeed = 15.0f;
	}
	else {
		camera.MovementSpeed = 5.0f;
	}

	TempKeyboardInput();
	TempMouseMove();

	if (inputManager->GetKey(70)) //speed up time. Literally.
	{
		if(!myTime.isPaused())
			myTime.Pause();
	}
	else {
		myTime.UnPause();
	}
}

void OrangeSherbetGameEngine::UpdateStuff() {
	std::vector<Light*> lightList = scene->GetListOfLights();
	lightList[0]->SetPosition(glm::vec3(sin(myTime.GetCurrentTime()) * 5, 1, cos(myTime.GetCurrentTime()) * 5));
	lightList[1]->SetPosition(glm::vec3(4.0f + sin(myTime.GetCurrentTime()*3.0f)*3.0f, 2.0f, 4.0f + cos(myTime.GetCurrentTime()*3.0f)*3.0f));
	lightList[2]->SetPosition(glm::vec3(-4.0f + sin(myTime.GetCurrentTime()*3.0f)*3.0f, 2.0f, 4.0f + cos(-myTime.GetCurrentTime()*3.0f)*3.0f));
	lightList[3]->SetPosition(glm::vec3(4.0f + sin(-myTime.GetCurrentTime()*3.0f)*3.0f, 2.0f, -4.0f + cos(myTime.GetCurrentTime()*3.0f)*3.0f));
	lightList[4]->SetPosition(glm::vec3(-4.0f + sin(-myTime.GetCurrentTime()*3.0f)*3.0f, 2.0f, -4.0f + cos(-myTime.GetCurrentTime()*3.0f)*3.0f));

	lightList[6]->SetDirection(camera.Front);
	lightList[6]->SetPosition(camera.Position);
	lightList[7]->SetDirection(glm::vec3(cos(myTime.GetCurrentTime()*3.0f)*30.0f, -10 + sin(myTime.GetCurrentTime()*12.0f)*60.0f, -5.0f));
	lightList[8]->SetDirection(glm::vec3(sin(myTime.GetCurrentTime()*5.0f)*60.0f, 50.0f, cos(myTime.GetCurrentTime()*4.0f)*30.0f));
	lightList[9]->SetDirection(glm::vec3(-1.0f, cos(myTime.GetCurrentTime()*3.0f)*30.0f, sin(myTime.GetCurrentTime()*5.0f)*50.0f));
	lightList[10]->SetDirection(glm::vec3(cos(myTime.GetCurrentTime()*13.0f)*30.0f, 1.0f, sin(myTime.GetCurrentTime()*3.0f)*30.0f));
}

void OrangeSherbetGameEngine::TempRun() {



	defaultShader = new Shader("Shaders/DefaultShader.vert", "Shaders/DefaultShader.frag");
	shader = new GLSLProgram();
	shader->compileShader("Shaders/DefaultShader.vert", GLSLShader::VERTEX);
	shader->compileShader("Shaders/DefaultShader.frag", GLSLShader::FRAGMENT);
	shader->link();

	camera.SetProjMatrix(projection);

	Texture* cubeTexture = new Texture("Assets/Models/Cube/albedo.png", 500, 500, (TextureType)0);
	Texture* specCubeTex = new Texture("Assets/Models/Cube/specular.png", 500, 500, (TextureType)1);

	Material* cMat = new Material(cubeTexture, specCubeTex);
	cMat->SetSpecular(glm::vec3(1, 1, 1));
	cMat->SetDiffuse(glm::vec3(0.5f, 0.5f, 0.5f));
	cMat->SetShininess(64);
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
	cubeTransform[2].SetLocalScale(glm::vec3(5, 1, 5));
	cubeTransform[2].SetLocalPosition(glm::vec3(0, -1.5, 0));

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
	tMat->SetShininess(256);
	tMat->SetSpecular(glm::vec3(1.0, 1.0, 1.0));
	Mesh* teapotMesh = LoadMeshNoNormals("Assets/Models/teapot/teapot.obj", tMat);
	Transform* teapotTransform = new Transform(camera.GetViewMatrix(), camera.GetProjMatrix());
	GameObject teapot(teapotTransform, teapotMesh, shader);


	scene->AddGameObject(&teapot);

	Texture* sibenikTexture = new Texture("Assets/Models/sibenik/kamen.png", 512, 512, (TextureType)0);
	Texture* sibenikSpecTexture = new Texture("Assets/Models/sibenik/mramor6x6.png", 512, 512, (TextureType)0);
	Material* sMat = new Material(sibenikTexture, sibenikSpecTexture);
	sMat->SetSpecular(glm::vec3(0.1, 0.1, 0.1));
	sMat->SetShininess(8);
	Mesh* sibenikMesh = LoadMeshNoNormals("Assets/Models/sibenik/sibenik.obj", sMat);
	Transform* sibenikTransform = new Transform(camera.GetViewMatrix(), camera.GetProjMatrix());
	sibenikTransform->SetLocalPosition(glm::vec3(0, 14, 0));
	GameObject sibenik(sibenikTransform, sibenikMesh, shader);

	scene->AddGameObject(&sibenik);
	
	//cml::mat4f model;
	teapot.transform->SetLocalPosition(glm::vec3(0, -1.0f, 0));
	teapot.transform->SetLocalScale(glm::vec3(0.01f, 0.015f, 0.01f));
	
	Light* dir = new Light(Color(1.0f, 0.95f, 0.6f), glm::vec3(0, 0, 0), glm::vec3(0, -15, 0), 0.5f, Light::LightType::Dir);
	Light* spot = new Light(Color(1.0f, 0.95f, 0.6f), glm::vec3(0, 10, 0), glm::vec3(0, 1, 0), 1.0f, glm::radians(8.5f), glm::radians(15.0f), Light::LightType::Spot);
	
	scene->AddLight(new Light(Colors::WHITE, glm::vec3(0.0f, 3.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.8f, Light::LightType::Point));
	scene->AddLight(new Light(Colors::RED, glm::vec3(4.0f, 2.0f, 4.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.6f, Light::LightType::Point));
	scene->AddLight(new Light(Colors::BLUE, glm::vec3(-4.0f, 2.0f, 4.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.6f, Light::LightType::Point));
	scene->AddLight(new Light(Colors::YELLOW, glm::vec3(4.0f, 2.0f, -4.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.6f, Light::LightType::Point));
	scene->AddLight(new Light(Colors::GREEN, glm::vec3(-4.0f, 2.0f, -4.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.6f, Light::LightType::Point));
	scene->AddLight(dir);
	scene->AddLight(spot);
	scene->AddLight(new Light(Colors::RED, glm::vec3(0, 10, 0), glm::vec3(0, 1, 0), 3.0f, glm::radians(8.5f), glm::radians(15.0f), Light::LightType::Spot));
	scene->AddLight(new Light(Colors::GREEN, glm::vec3(0, 10, 0), glm::vec3(0, 1, 0), 3.0f, glm::radians(8.5f), glm::radians(15.0f), Light::LightType::Spot));
	scene->AddLight(new Light(Colors::BLUE, glm::vec3(0, 10, 0), glm::vec3(0, 1, 0), 3.0f, glm::radians(8.5f), glm::radians(15.0f), Light::LightType::Spot));
	scene->AddLight(new Light(Colors::YELLOW, glm::vec3(0, 10, 0), glm::vec3(0, 1, 0), 3.0f, glm::radians(8.5f), glm::radians(15.0f), Light::LightType::Spot));


	// Main Game loop
	while (!glfwWindowShouldClose(window->getGLFWWindow()))
	{
		ProcessInputs();

		myTime.TickClock();
		//myTime.PrintCurrentTime();

		if (window->windowSizeChanged) {
			camera.SetProjMatrix(glm::perspective(glm::radians(camera.Zoom), (float)window->getWidth() / (float)window->getHeight(), 0.01f, 1000.0f));
			scene->UpdateProjectionMatrix(camera.GetProjMatrix());
			window->windowSizeChanged = false;
		}

		// Render
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //Set the background to a nice muted green
		//glClearColor(sin(myTime.GetCurrentTime()), 0.3f, 0.3f, 1.0f); //Set the background to a nice muted green
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Clear the colorbuffer


		glm::mat4 view = camera.GetViewMatrix();

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
		
		teapot.transform->SetLocalRotation(0, myTime.GetCurrentTime(), 0);
		//teapot.transform->SetLocalScale(0.01f, 0.01f*(1.5f + sin(myTime.GetCurrentTime())/3), 0.01f);

		UpdateStuff();

		scene->DrawScene(view);
		//simple flashliht toggle. press T to turn on, G to turn off
		if (inputManager->GetKey(71)) 
			spot->SetIntensity(0.0f);
		if (inputManager->GetKey(84))
			spot->SetIntensity(1.0f);
		

		//std::cout << "Camera position = " << camera.Position << "Camera Lookint at position = " << camera.Front <<std::endl;

		// Swap the screen buffers
		glfwSwapBuffers(window->getGLFWWindow());

	}

	ShutDown();
}
