
#include <iostream>
#include "CML\cml.h"

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "OrangeSherbetGameEngine.h"

#include "Shader.h"

#include "CameraGLM.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void OnMouseMoved(GLFWwindow* window, double xpos, double ypos);
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

void OnMouseButton(GLFWwindow* window, int glfwButton, int glfwAction);

// Default Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

GLFWwindow *window;

GLuint VAO, VBO, EBO;
GLuint triangleVBO, triangleVAO;

Camera camera(glm::vec3(-3, 0, 0));

GLfloat cubeVerts[] = {
	 -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	 -0.5f, 0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
	0.5f, 0.5f, -0.5f,	 1.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f,	 1.0f, 1.0f, 0.0f,
	0.5f,-0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	-0.5f,-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,

	-0.5f,-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, 0.5f,  0.5f,	 1.0f, 0.0f, 1.0f,
	0.5f, 0.5f,  0.5f,	 1.0f, 1.0f, 1.0f,
	0.5f, 0.5f,  0.5f,	 1.0f, 1.0f, 1.0f,
	0.5f,-0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
	-0.5f,-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,

	0.5f,-0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
	0.5f,-0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	-0.5f,-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	-0.5f,-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	-0.5f,-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
	0.5f,-0.5f,  0.5f, 0.0f, 1.0f, 1.0f,

	0.5f, 0.5f,  0.5f,	 1.0f, 1.0f, 1.0f,
	0.5f, 0.5f, -0.5f,	 1.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, -0.5f,	 1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f,	 1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f,  0.5f,	 1.0f, 0.0f, 1.0f,
	0.5f, 0.5f,  0.5f,	 1.0f, 1.0f, 1.0f,

	-0.5f,-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f,	 1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f,  0.5f,	 1.0f, 0.0f, 1.0f,
	-0.5f, 0.5f,  0.5f,	 1.0f, 0.0f, 1.0f,
	-0.5f,-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f,-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,

	0.5f,-0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f,	 1.0f, 1.0f, 0.0f,
	0.5f, 0.5f,  0.5f,	1.0f, 1.0f, 1.0f,
	0.5f, 0.5f,  0.5f,	1.0f, 1.0f, 1.0f,
	0.5f,-0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
	0.5f,-0.5f, -0.5f, 0.0f, 1.0f, 0.0f
};

GLfloat triangle[] = {
	0,0,0, 1,0,0,
	0,1,0, 0,1,0,
	1,0,0, 0,0,1
};

void setup_window() {
	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl; //for now use a version thats going to work regardless
  
	// Init GLFW
	if (!glfwInit())
		exit(EXIT_FAILURE);
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 4);


	// Create a GLFWwindow object that we can use for GLFW's functions
	window = glfwCreateWindow(WIDTH, HEIGHT, "Terrain FPS", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	//glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)OnMouseButton);
	glfwSetCursorPosCallback(window, OnMouseMoved);
	//glfwSetScrollCallback(window, OnScrollMoved);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;

	glfwSwapInterval(1);

	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();
}

void setup_vao() {
	// Set up vertex data (and buffer(s)) and attribute pointers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 6 * 36 * sizeof(GLfloat), cubeVerts, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);					
													
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Normal attribute

	glBindVertexArray(0); // Unbind VAO
}

int main() {
	std::cout << "Starting up the Orange Sherbet Game Engine, Version idgaf" << std::endl;

	Osge::OrangeSherbetGameEngine * osge = new Osge::OrangeSherbetGameEngine();

	osge->StartUp();

	setup_window();

	Shader defaultShader("DefaultVertexShader.glsl", "DefaultFragmentShader.glsl");

	std::string img_fileName = "TestTexture.png";

	int w = 256;
	int h = 256;
	int comp;
	unsigned char* image = stbi_load(img_fileName.c_str(), &w, &h, &comp, STBI_rgb_alpha);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);

	// Define the viewport dimensions
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);

	setup_vao();

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

		// Draw the triangle
		defaultShader.Use();
		//glBindVertexArray(VAO);

		glm::mat4 view = camera.GetViewMatrix();
		//cml::mat4f view = camera.GetViewMatrix();
		//cml::mat4f projection = cml::mat4f::createPerspective(cml::degToRad(camera.Zoom), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 1000.0f);
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.01f, 100000.0f);

		glm::mat4 model = glm::mat4();
		
		GLint modelLoc = glGetUniformLocation(defaultShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(defaultShader.Program, "view");
		GLint projLoc = glGetUniformLocation(defaultShader.Program, "projection");

		
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		//glUniformMatrix4fv(projLoc, 1, GL_FALSE, cml::mat4f::value_ptr(projection));
		//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, cml::mat4f::value_ptr(view));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		//std::cout << "Camera position = " << camera.Position << "Camera Lookint at position = " << camera.Front <<std::endl;

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

	glDeleteBuffers(1, &VBO);

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	std::cout << key << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	float deltaTime = 0.05f;

	// Camera controls
	if (key == GLFW_KEY_W)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (key == GLFW_KEY_S)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (key == GLFW_KEY_A)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (key == GLFW_KEY_D)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (key == GLFW_KEY_Q)
		camera.ProcessKeyboard(DOWN, deltaTime);
	if (key == GLFW_KEY_E)
		camera.ProcessKeyboard(UP, deltaTime);
}

void OnMouseMoved(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

	lastX = xpos;
	lastY = ypos;

	std::cout << "Mouse Moved" << std::endl;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void OnMouseButton(GLFWwindow* window, int glfwButton, int glfwAction) {
	//mouseHeldDown = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
		std::cout << "Left Clicked" << std::endl;
}