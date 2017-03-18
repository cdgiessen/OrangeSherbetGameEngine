#include "InputManager.h"

#include <GLFW\glfw3.h>

namespace Osge {

	InputManager::InputManager(GLFWwindow* window)
	{
		this->window = window;
		inputManager = this;
	}


	InputManager::~InputManager()
	{
	}

	void InputManager::SetUp(){
		//glfwSetKeyCallback(window, (GLFWkeyfun)KeyPressedCallback);
		//		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		//		glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)(ipm->UpdateMousButton));
		//		glfwSetCursorPosCallback(window, ipm->UpdateMouseMoved);
		//		glfwSetScrollCallback(window, ipm->UpdateScrollMoved);
		//register callbacks
	}


	bool InputManager::GetKey(int key) {
		if (key >= 0 && key < inputArraySize)
			return keys[key];
	}

	void KeyPressedCallback(GLFWwindow& window, int key, int scancode, int action, int mode) {
		//inputMan->UpdateKeyPressed(window, key, scancode, action, mode);
	}
	void InputManager::UpdateKeyPressed(GLFWwindow& window, int key, int scancode, int action, int mode) {
		
		if (key >= 0 && key < inputArraySize)
		{
			if (action == GLFW_PRESS)
				keys[key] = true;
			else if (action == GLFW_RELEASE)
				keys[key] = false;
		}
	}


	void MouseMovedCallback(GLFWwindow& window, double xpos, double ypos) {
		//inputMan->UpdateMouseMoved(window, xpos, ypos);
	}
	void InputManager::UpdateMouseMoved(GLFWwindow& window, double xpos, double ypos) {

	}


	void MouseButtonCallback(GLFWwindow& window, int glfwButton, int glfwAction) {
		//inputMan->UpdateMouseButton(window, glfwButton, glfwAction);
	}
	void InputManager::UpdateMouseButton(GLFWwindow& window, int glfwButton, int glfwAction) {


	}


	void ScrollWheelMovedCallback(GLFWwindow& window, double xoffset, double yoffset) {
		//inputMan->UpdateScrollMoved(window, xoffset, yoffset);
	}
	void InputManager::UpdateScrollMoved(GLFWwindow& window, double xoffset, double yoffset) {


	}
}