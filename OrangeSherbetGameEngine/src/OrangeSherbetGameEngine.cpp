#include "OrangeSherbetGameEngine.h"
#include <iostream>
#include <unordered_map>

#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define TINYOBJLOADER_IMPLEMENTATION
//#include <tinyobj_loader_opt.h>
#include <tiny_obj_loader.h>

//#include "CML\cml.h"
//#include "CML\mat4.h"

// Default Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

GLFWwindow *window;

//void OnMouseButton(GLFWwindow* window, int glfwButton, int glfwAction);

//GLuint VAO, VBO, EBO;
//GLuint triangleVBO, triangleVAO;

Camera camera(glm::vec3(-3, 0, 0));

glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.01f, 10000.0f);

Shader* defaultShader;
GLSLProgram* shader;
Texture* cubeTexture;
Mesh* cubeMesh;
Mesh* quadMesh;


OrangeSherbetGameEngine::OrangeSherbetGameEngine() {
	StartUp();
}


OrangeSherbetGameEngine::~OrangeSherbetGameEngine() {}

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

	std::cout << "Bye bye!" << std::endl; //y u ! werk?
	return 0;
}


void OrangeSherbetGameEngine::TempRun() {
	defaultShader = new Shader("Shaders/DefaultVertexShader.glsl", "Shaders/DefaultFragmentShader.glsl");
	shader = new GLSLProgram();
	shader->compileShader("Shaders/DefaultVertexShader.glsl", GLSLShader::VERTEX);
	shader->compileShader("Shaders/DefaultFragmentShader.glsl", GLSLShader::FRAGMENT);
	shader->link();
	glm::mat4 initCameraView(camera.GetViewMatrix());
	glm::mat4 perspectiveProjection(glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.01f, 100.0f));

	//cubeTexture = new Texture("Assets/Images/SolidColorCube.png", 96, 64, (TextureType)0);
	cubeTexture = new Texture("Assets/Models/Cube/default.png", 128, 128, (TextureType)0);
	Texture* specCubeTex = new Texture("Assets/Models/Cube/specular.png", 128, 128, (TextureType)1);
	Material* cMat = new Material(cubeTexture, specCubeTex);
	//cubeMesh = LoadMesh("Assets/Models/cube/cube.obj", cMat);
	cubeMesh = LoadCubeMesh(cMat);
	Transform cubeTransform[6]{ 
		Transform(initCameraView, perspectiveProjection),
		Transform(initCameraView, perspectiveProjection),
		Transform(initCameraView, perspectiveProjection),
		Transform(initCameraView, perspectiveProjection),
		Transform(initCameraView, perspectiveProjection),
		Transform(initCameraView, perspectiveProjection) };

	cubeTransform[0].SetLocalPosition(glm::vec3(3, 0, 0));
	cubeTransform[0].SetLocalScale(glm::vec3(1, 1, 1.5));
	cubeTransform[1].SetLocalPosition(glm::vec3(0, 0, 3));
	cubeTransform[2].SetLocalPosition(glm::vec3(0, -3, 0));
	cubeTransform[2].SetLocalScale(glm::vec3(15, 1, 15));
	cubeTransform[3].SetLocalPosition(glm::vec3(0, 3, 0));
	cubeTransform[4].SetLocalPosition(glm::vec3(0, 0, -3));	
	cubeTransform[5].SetLocalPosition(glm::vec3(-3, 0, 0));


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

	std::vector<Vertex> teapotVertices;
	std::vector<GLuint> teapotIndices;

	std::string inputfile = "Assets/Models/teapot/teapot.obj";
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err;
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, inputfile.c_str());

	if (!err.empty()) { // `err` may contain warning message.
		std::cerr << err << std::endl;
	}

	if (!ret) {
		exit(1);
	}

	std::unordered_map<Vertex, int> uniqueVertices = {};

	for (const auto& shape : shapes) {
		for (const auto& index : shape.mesh.indices) {
			Vertex vertex = {};

			vertex.Position = {
				attrib.vertices[3 * index.vertex_index + 0],
				attrib.vertices[3 * index.vertex_index + 1],
				attrib.vertices[3 * index.vertex_index + 2]
			};

			vertex.TexCoords = {
				attrib.texcoords[2 * index.texcoord_index + 0],
				1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
			};
			
			
			vertex.Normal = { vertex.Position.x, vertex.Position.y, vertex.Position.z };

			//std::cout << vertex.Position.x << vertex.Position.y << vertex.Position.z << std::endl;

			if (uniqueVertices.count(vertex) == 0) {
				uniqueVertices[vertex] = teapotVertices.size();
				teapotVertices.push_back(vertex);
			}

			teapotIndices.push_back(uniqueVertices[vertex]);
		}
	}


	Texture* teapotTexture = new Texture("Assets/Models/teapot/colorful.png", 128, 128, (TextureType)0);
	Material* tMat = new Material(teapotTexture);
	Mesh* teapotMesh = new Mesh(teapotVertices, teapotIndices, tMat);
	Transform* teapotTransform = new Transform(initCameraView, perspectiveProjection);
	GameObject teapot(teapotTransform, teapotMesh, shader);

	scene->AddGameObject(&teapot);

	//cml::mat4f model;
	teapot.transform->SetLocalScale(glm::vec3(0.01f, 0.01f, 0.01f));
	//setup_vao();

	Light l0(Color(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.7f, Light::LightType::Point);
	Light l1(Color(1.0f, 0.0f, 0.0f), glm::vec3(3.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, Light::LightType::Point);
	Light l2(Color(0.0f, 0.0f, 1.0f), glm::vec3(-3.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, Light::LightType::Point);
	Light l3(Color(1.0f, 1.0f, 0.0f), glm::vec3(3.0f, 0.0f, -3.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, Light::LightType::Point);
	Light l4(Color(0.0f, 1.0f, 0.0f), glm::vec3(-3.0f, 0.0f, -3.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, Light::LightType::Point);
	


	scene->AddLight(&l0);
	scene->AddLight(&l1);
	scene->AddLight(&l2);
	scene->AddLight(&l3);
	scene->AddLight(&l4);

	float timeish = 0;

	// Main Game loop
	while (!glfwWindowShouldClose(window->getGLFWWindow()))
	{
		if (inputManager->GetKey(70)) //speed up time. Literally.
			timeish += 0.016f * 5;
		timeish += 0.016f;
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		if (window->windowSizeChanged) {
			perspectiveProjection = glm::perspective(glm::radians(camera.Zoom), (float)window->getWidth() / (float)window->getHeight(), 0.01f, 1000.0f);
			scene->UpdateProjectionMatrix(perspectiveProjection);
			window->windowSizeChanged = false;
		}

		TempKeyboardInput();
		TempMouseMove();

		// Render
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //Set the background to a nice muted green
		//glClearColor(sin(timeish), 0.3f, 0.3f, 1.0f); //Set the background to a nice muted green
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Clear the colorbuffer


		// Draw the triangle
		//DrawCube();

		glm::mat4 view = camera.GetViewMatrix();

		//RENDER
		cubeObject0.transform->SetLocalRotation(0, timeish, 0);
		cubeObject1.transform->SetLocalRotation(270, timeish, 45);
		//cubeObject2.transform->SetLocalRotation(0, timeish/8, 0);
		//cubeObject2.transform->SetLocalPosition(glm::vec3(0.0f, 3.0f + sin(timeish*1.5f) * 1, 0));
		cubeObject3.transform->SetLocalRotation(45, timeish*1.5f, 0);
		cubeObject4.transform->SetLocalRotation(timeish*3.0f, timeish*1.667f , 0);
		cubeObject5.transform->SetLocalRotation(timeish, timeish *2, timeish/1.5f);
		
		//for (int i = 0; i < 6; i++) {
		//	cubeObject[i].Draw(view);
		//}

		teapot.transform->SetLocalRotation(0, timeish, 0);
		teapot.transform->SetLocalScale(0.01f, 0.01f*(1.5f + sin(timeish)/3), 0.01f);
		//teapot.transform->
		//teapot.Draw(view);

		l1.SetPosition(glm::vec3(3.0f, 0.0f, sin(timeish*3.0f)*3.0f));		
		
		//(scene->GetListOfLights())[1]->SetPosition(glm::vec3(-3, 0, cos(timeish*3.0f)*.0f));
		//(scene->GetListOfLights())[2]->SetPosition(glm::vec3(sin(timeish*3.0f) * 3.0f, 0, 3.0f));
		//(scene->GetListOfLights())[3]->SetPosition(glm::vec3(sin(timeish*3.0f) * 3.0f, 0, -3.0f));
		
		scene->DrawScene(view);

		//std::cout << "Camera position = " << camera.Position << "Camera Lookint at position = " << camera.Front <<std::endl;

		// Swap the screen buffers
		glfwSwapBuffers(window->getGLFWWindow());
	}

	ShutDown();
}
