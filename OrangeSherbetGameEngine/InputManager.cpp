#include "InputManager.h"

InputManager::InputManager(GLFWwindow* window)
{
	inputManager = this;
	glfwWindow = window;
	glfwSetKeyCallback(window, (GLFWkeyfun)KeyPressedCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)(MouseMovedCallback));
	glfwSetCursorPosCallback(window, (GLFWcursorposfun)MouseButtonCallback);
	glfwSetScrollCallback(window, (GLFWscrollfun)ScrollWheelMovedCallback);
	//register callbacks
}


InputManager::~InputManager()
{
}

bool InputManager::GetKey(int key) {
	if (key >= 0 && key < inputArraySize)
		return keys[key];
}

void KeyPressedCallback(GLFWwindow& window, int key, int scancode, int action, int mode) {
	inputManager->UpdateKeyPressed(window, key, scancode, action, mode);
}
void InputManager::UpdateKeyPressed(GLFWwindow& window, int key, int scancode, int action, int mode) {

	std::cout << key << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(&window, GL_TRUE);
	if (key >= 0 && key < inputArraySize)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}


void MouseMovedCallback(GLFWwindow& window, double xpos, double ypos) {
	inputManager->UpdateMouseMoved(window, xpos, ypos);
}
void InputManager::UpdateMouseMoved(GLFWwindow& window, double xpos, double ypos) {

}


void MouseButtonCallback(GLFWwindow& window, int glfwButton, int glfwAction) {
	inputManager->UpdateMouseButton(window, glfwButton, glfwAction);
}
void InputManager::UpdateMouseButton(GLFWwindow& window, int glfwButton, int glfwAction) {


}


void ScrollWheelMovedCallback(GLFWwindow& window, double xoffset, double yoffset) {
	inputManager->UpdateScrollMoved(window, xoffset, yoffset);
}
void InputManager::UpdateScrollMoved(GLFWwindow& window, double xoffset, double yoffset) {


}
