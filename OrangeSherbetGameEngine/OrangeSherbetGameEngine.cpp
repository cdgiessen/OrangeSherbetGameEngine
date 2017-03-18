#include "OrangeSherbetGameEngine.h"
#include <iostream>

#include "Shader.h"

namespace Osge {

	OrangeSherbetGameEngine::OrangeSherbetGameEngine()
	{
	}


	OrangeSherbetGameEngine::~OrangeSherbetGameEngine()
	{
	}

	int OrangeSherbetGameEngine::StartUp() {
		inputManager = new Osge::InputManager();


		return 0;
	}

	int OrangeSherbetGameEngine::ShutDown() {
		return 0;
	}
}