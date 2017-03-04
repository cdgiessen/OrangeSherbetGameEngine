#include "InputManager.h"

namespace Osge {

	InputManager::InputManager(GLFWwindow& window)
	{

		//register callbacks
	}


	InputManager::~InputManager()
	{
	}

	bool InputManager::GetKey(int key) {
		if (key >= 0 && key < inputArraySize)
			return keys[key];
	}

	void InputManager::UpdateKey(GLFWwindow* window, int key, int scancode, int action, int mode) {
		
		if (key >= 0 && key < inputArraySize)
		{
			if (action == GLFW_PRESS)
				keys[key] = true;
			else if (action == GLFW_RELEASE)
				keys[key] = false;
		}
	}
}