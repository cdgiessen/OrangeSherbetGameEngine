#pragma once

#include <GLFW\glfw3.h>

namespace Osge {

	class InputManager
	{
	public:
		InputManager(GLFWwindow& window);
		~InputManager();

		bool GetKey(int key);

		void UpdateKey(GLFWwindow* window, int key, int scancode, int action, int mode);

	private:
		static const int inputArraySize = 1024;
		bool keys[inputArraySize];

		enum keyCode {

		};
	};
}

