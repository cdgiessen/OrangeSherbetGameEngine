#include "../include/OrangeSherbetGameEngine.h"

#include <iostream>


void start() {
	OrangeSherbetGameEngine pOsge;

	pOsge.StartUp();
	pOsge.TempRun();

}

int main() {
	start();

	std::cout << std::endl;
	return 0;
}


