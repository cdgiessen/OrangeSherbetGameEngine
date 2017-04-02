#include "../include/InputManager.h"

InputManager::InputManager(GLFWwindow* window)
{
	glfwWindow = window;
	im = this;
	//register callbacks
	glfwSetKeyCallback(window, (GLFWkeyfun)KeyPressedCallback);
	glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)(MouseButtonCallback));
	glfwSetCursorPosCallback(window, (GLFWcursorposfun)MouseMovedCallback);
	glfwSetScrollCallback(window, (GLFWscrollfun)ScrollWheelMovedCallback);


}


InputManager::~InputManager()
{
}

bool InputManager::GetKey(int key) {
	if (key >= 0 && key < keyArraySize)
		return keys[key];
}

void KeyPressedCallback(GLFWwindow& window, int key, int scancode, int action, int mode) {
	im->UpdateKeyPressed(window, key, scancode, action, mode);
}
void InputManager::UpdateKeyPressed(GLFWwindow& window, int key, int scancode, int action, int mode) {

	std::cout << key << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(&window, GL_TRUE);
	if (key >= 0 && key < keyArraySize)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}


void MouseMovedCallback(GLFWwindow& window, double xpos, double ypos) {
	im->UpdateMouseMoved(window, xpos, ypos);
}
void InputManager::UpdateMouseMoved(GLFWwindow& window, double xpos, double ypos) {
	if (firstMouse)
	{
		m_lastX = xpos;
		m_lastY = ypos;
		firstMouse = false;
	}

	m_xoffset = xpos - m_lastX;
	m_yoffset = m_lastY - ypos;  // Reversed since y-coordinates go from bottom to left

	m_xpos = xpos;
	m_ypos = ypos;

	m_lastX = xpos;
	m_lastY = ypos;

	//std::cout << " lastX " << m_lastX << " lasty " << m_lastY << " xoffset " << xoffset << " yoffset " << yoffset << std::endl;
}


void MouseButtonCallback(GLFWwindow& window, int glfwButton, int glfwAction) {
	im->UpdateMouseButton(window, glfwButton, glfwAction);
}
void InputManager::UpdateMouseButton(GLFWwindow& window, int glfwButton, int glfwAction) {
	std::cout << "Mouse button " << glfwButton << " with action " << glfwAction << std::endl;
	mouseButtons[glfwButton] = glfwAction;
}


void ScrollWheelMovedCallback(GLFWwindow& window, double xoffset, double yoffset) {
	im->UpdateScrollMoved(window, xoffset, yoffset);
}
void InputManager::UpdateScrollMoved(GLFWwindow& window, double xoffset, double yoffset) {


}


float InputManager::GetMousePositionX() { return m_xpos; }
float InputManager::GetMousePositionY() { return m_ypos; }

float InputManager::GetMouseOffsetPositionX() { return m_xoffset; }
float InputManager::GetMouseOffsetPositionY() { return m_yoffset; }
