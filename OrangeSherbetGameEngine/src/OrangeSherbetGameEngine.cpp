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

#include "MeshPrimitives.h"

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
	glm::mat4 initCameraView(camera.GetViewMatrix());
	glm::mat4 perspectiveProjection(glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.01f, 100.0f));

	cubeTexture = new Texture("Assets/Images/SolidColorCube.png", 96, 64, (TextureType)0);
	Material* cMat = new Material(cubeTexture);
	cubeMesh = LoadMesh("Assets/Models/cube/cube.obj", cMat);

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
	
	cubeTransform[2].SetLocalPosition(glm::vec3(0, 3, 0));
	cubeTransform[2].SetLocalScale(glm::vec3(3, 1, 3));

	cubeTransform[3].SetLocalPosition(glm::vec3(0, -3, 0));
	
	cubeTransform[4].SetLocalPosition(glm::vec3(0, 0, -3));
	
	cubeTransform[5].SetLocalPosition(glm::vec3(-3, 0, 0));

	//m5.rotate(cml::vec3f(0, 0, 1), 0);
	//m5.scale(cml::vec3f(1, 2, 1));
	//m5.translate(cml::vec3f(-4, 0, 0));
	//cubeTransform[4].SetModelMatrix(m5);

	//m6.rotate(cml::vec3f(0, 0, 1), 3.14f/2.0f);
	//m6.scale(cml::vec3f(1, 2, 1));
	//m6.translate(cml::vec3f(-1, 0, 0));	

	GameObject cubeObject[6]{ GameObject(&cubeTransform[0], cubeMesh, defaultShader),
		GameObject(&cubeTransform[1], cubeMesh, defaultShader),
		GameObject(&cubeTransform[2], cubeMesh, defaultShader),
		GameObject(&cubeTransform[3], cubeMesh, defaultShader),
		GameObject(&cubeTransform[4], cubeMesh, defaultShader),
		GameObject(&cubeTransform[5], cubeMesh, defaultShader)
	};

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
	Mesh* teapotMesh = new Mesh(teapotVertices,teapotIndices, tMat);
	Transform* teapotTransform = new Transform(initCameraView, perspectiveProjection);
	GameObject teapot(teapotTransform, teapotMesh, defaultShader);

	//cml::mat4f model;
	teapot.transform->SetLocalScale(glm::vec3(0.01f, 0.01f, 0.01f));
	//setup_vao();

	float timeish = 0;

	// Main Game loop
	while (!glfwWindowShouldClose(window->getGLFWWindow()))
	{
		if (inputManager->GetKey(70)) //speed up time. Literally.
			timeish += 0.016f * 5;
		timeish += 0.016f;
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

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
		cubeObject[0].transform->SetLocalRotation(45, timeish, 0);
		cubeObject[1].transform->SetLocalRotation(270, timeish, 45);
		cubeObject[2].transform->SetLocalRotation(0, timeish/4, 0);
		cubeObject[2].transform->SetLocalPosition(glm::vec3(0.0f, 3.0f + sin(timeish*1.5f) * 1, 0));
		cubeObject[3].transform->SetLocalRotation(45, timeish*1.5f, 0);
		cubeObject[4].transform->SetLocalRotation(timeish*3.0f, timeish*1.667f , 0);
		cubeObject[5].transform->SetLocalRotation(timeish, timeish *2, timeish/1.5f);
		
		for (int i = 0; i < 6; i++) {
			cubeObject[i].Draw(view);
		}

		teapot.transform->SetLocalRotation(0, timeish, 0);
		teapot.transform->SetLocalScale(0.01f, 0.01f*(1.5f + sin(timeish)/3), 0.01f);
		//teapot.transform->
		teapot.Draw(view);

		//std::cout << "Camera position = " << camera.Position << "Camera Lookint at position = " << camera.Front <<std::endl;

		// Swap the screen buffers
		glfwSwapBuffers(window->getGLFWWindow());
	}

	ShutDown();
}
