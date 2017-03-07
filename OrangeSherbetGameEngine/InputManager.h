#pragma once

#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <GLFW\glfw3.h>

namespace Osge {

	

	class InputManager
	{
	public:
		InputManager();
		InputManager(GLFWwindow* window);
		~InputManager();

		bool GetKey(int key);

		void UpdateKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mode);

		void UpdateMouseMoved(GLFWwindow* window, double xpos, double ypos);

		void UpdateMousButton(GLFWwindow* window, int glfwButton, int glfwAction);

		void UpdateScrollMoved(GLFWwindow* window, double xoffset, double yoffset);

	private:
		static const int inputArraySize = 1024;
		bool keys[inputArraySize];

		enum keyCode {

		};
	};
}

#endif // !INPUT_MANAGER_H
