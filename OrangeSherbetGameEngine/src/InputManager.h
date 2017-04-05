#pragma once

#include <GLFW\glfw3.h>
#include <iostream>

void KeyPressedCallback(GLFWwindow& window, int key, int scancode, int action, int mode);
void MouseMovedCallback(GLFWwindow& window, double xpos, double ypos);
void MouseButtonCallback(GLFWwindow& window, int glfwButton, int glfwAction);
void ScrollWheelMovedCallback(GLFWwindow& window, double xoffset, double yoffset);

static const int keyArraySize = 1024;
static bool keys[keyArraySize];

class InputManager
{
public:

	InputManager(GLFWwindow* window);
	~InputManager();

	bool GetKey(int key);

	float GetMousePositionX();
	float GetMousePositionY();

	float GetMouseOffsetPositionX();
	float GetMouseOffsetPositionY();

	//TEMPORARY HACK CAUSE THE GAME POLLS THE OFFSET EVERYFRAME WHEN IT SHOULD ONLY BE WHEN THE MOUSE MOVES (EVENT)
	void ResetMouseOffset() {
		m_xoffset = 0;
		m_yoffset = 0;
	}

	void UpdateKeyPressed(GLFWwindow& window, int key, int scancode, int action, int mode);

	void UpdateMouseMoved(GLFWwindow& window, double xpos, double ypos);

	void UpdateMouseButton(GLFWwindow& window, int glfwButton, int glfwAction);

	void UpdateScrollMoved(GLFWwindow& window, double xoffset, double yoffset);

private:
	GLFWwindow *glfwWindow;


	//static const int keyArraySize = 1024;
	//bool keys[keyArraySize];

	float m_xpos = 400;
	float m_ypos = 300;
	float m_lastX = 400, m_lastY = 300;
	bool firstMouse = true;
	float m_xoffset = 0;
	float m_yoffset = 0;

	bool mouseButtons[8];

	enum keyCode {

	};
};

static InputManager* im;



