#include "InputManager.h"

#include <GLFW\glfw3.h>

namespace Osge {

	InputManager::InputManager(GLFWwindow* window)
	{
		InputManager *ipm = this;
//		glfwSetKeyCallback(window, ipm->UpdateKeyPressed);
//		//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//		glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)(ipm->UpdateMousButton));
//		glfwSetCursorPosCallback(window, ipm->UpdateMouseMoved);
//		glfwSetScrollCallback(window, ipm->UpdateScrollMoved);
		//register callbacks
	}


	InputManager::~InputManager()
	{
	}

	bool InputManager::GetKey(int key) {
		if (key >= 0 && key < inputArraySize)
			return keys[key];
	}

	void InputManager::UpdateKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mode) {
		
		if (key >= 0 && key < inputArraySize)
		{
			if (action == GLFW_PRESS)
				keys[key] = true;
			else if (action == GLFW_RELEASE)
				keys[key] = false;
		}
	}

	void InputManager::UpdateMouseMoved(GLFWwindow* window, double xpos, double ypos) {

	}

	void InputManager::UpdateMousButton(GLFWwindow* window, int glfwButton, int glfwAction) {


	}

	void InputManager::UpdateScrollMoved(GLFWwindow* window, double xoffset, double yoffset) {


	}
}