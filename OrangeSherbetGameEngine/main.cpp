
#include <iostream>
#include "CML\cml.h"

#include <cstdlib> //for rand()
#include <chrono> //for timer

typedef std::chrono::high_resolution_clock Clock; //gets me a timer

void main() {
	std::cout << "Starting up the Oarnge Sherbet Game Engine, Version 0.0.1" << std::endl;
	
	std::cout << "Begin vertex tests" << std::endl << std::endl;
	const int vecTestSize = 50000;
	cml::vec3f vectors[vecTestSize];

	auto rotMatrix = cml::mat4f::createRotationMatrix(15.0, 25.0, 180.0);
	auto transMatrix = cml::mat4f::createTranslationMatrix( cml::vec3f(10.0, -4.0, 25.0));
	auto scaleMatrix = cml::mat4f::createTranslationMatrix(cml::vec3f(0.12, 3.1, 2.5));
	auto tranformationMatrix = rotMatrix * transMatrix * scaleMatrix;

	for (int i = 0; i < vecTestSize; i++)
	{
		vectors[i] = cml::vec3f(rand() % 200 - 100, rand() % 200 - 100, rand() % 200 - 100);
		//std::cout << vectors[i] << std::endl;
	}

	std::cout << "Multiplying vectors by rotation matrix (15, 25, 180)" << std::endl;

	auto beginCount = Clock::now();
	for (int i = 0; i < vecTestSize; i++)
	{
		vectors[i] = tranformationMatrix * vectors[i];
	}
	auto endCount = Clock::now();

	std::cout << "Time taken to compute " << vecTestSize << " vector multiplications is " << std::chrono::duration_cast<std::chrono::nanoseconds>(endCount - beginCount).count() << " nanoseconds" << std::endl;


	std::cout << "Press any key to continue..." << std::endl;
	std::getchar();
}