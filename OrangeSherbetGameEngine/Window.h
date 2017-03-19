#pragma once

#include <gl/glew.h>
#include <GLFW\glfw3.h>
#include <CML\cml.h>

namespace Osge {

	class Window
	{
	public:
		Window(int height, int width, bool fullscreen, char *title);
		~Window();

		
		GLFWwindow *getGLFWWindow();
		int getHeight();
		int getWidth();
		bool isFullscreen();
		bool isClosed();

		// Tell window to close
		void close();

	private:
		int HEIGHT;                     // Height of window
		int WIDTH;                      // Width of window
		bool fullscreen;                // Is window fullscreen?
		bool shouldClose;               // Should window close?
		char *title;                    // Title of window
		GLFWwindow *window;             // Window for GLFW
		double timeSinceLastFrame;      // Time since last frame
		double lastFrameTime; // Time last frame was reported

		cml::mat4f projectionMatrix; //Perspective matrix for the window (used so resizing window doesn't mess stuff up)
		//static Window *myWindow;			//Window reference for resize callback

		void init(); // Initializes window with GLFW

		// Callback registered with GLFW in init() to change the glViewport to match the new window size
		// TODO: Figure out if this needs to remain static or what should be done
		static void window_size_callback(GLFWwindow *window, int newWidth, int newHeight);
	};

}