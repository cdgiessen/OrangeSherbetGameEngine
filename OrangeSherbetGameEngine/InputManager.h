#pragma once

#include <GLFW\glfw3.h>

namespace Osge {

	void KeyPressedCallback(GLFWwindow& window, int key, int scancode, int action, int mode);
	void MouseMovedCallback(GLFWwindow& window, double xpos, double ypos);
	void MouseButtonCallback(GLFWwindow& window, int glfwButton, int glfwAction);
	void ScrollWheelMovedCallback(GLFWwindow& window, double xoffset, double yoffset);

	class InputManager
	{
	public:
		
		InputManager(GLFWwindow* window);
		~InputManager();

		void SetUp();

		bool GetKey(int key);
				
		void UpdateKeyPressed(GLFWwindow& window, int key, int scancode, int action, int mode);
										
		void UpdateMouseMoved(GLFWwindow& window, double xpos, double ypos);
										
		void UpdateMouseButton(GLFWwindow& window, int glfwButton, int glfwAction);

		void UpdateScrollMoved(GLFWwindow& window, double xoffset, double yoffset);

	private:
		GLFWwindow *window;


		static const int inputArraySize = 1024;
		bool keys[inputArraySize];

		enum keyCode {

		};
	};

	static InputManager *inputManager;
}

