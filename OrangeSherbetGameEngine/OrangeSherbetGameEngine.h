#pragma once

namespace Osge {

	//All the subsystems.
	//Memory Manager (pool, stack, etc)
	//File System(resource loading and save state loading)
	
	//Rendering/animation/texture graphics	
	//Physics manager


	class OrangeSherbetGameEngine
	{
	public:
		OrangeSherbetGameEngine();
		~OrangeSherbetGameEngine();

		void StartUp (){
			//Start pointers to subsystems
		};

		void ShutDown() {
			//Shut them down in reverse order	
		};
	};

}

