
//#include "CML\cml.h"
#include <glm\vec3.hpp>
#include <glm/mat4x4.hpp>
#include <vector>

#include <iostream>

#include <cstdlib> //for rand()
#include <chrono> //for timer

typedef std::chrono::high_resolution_clock Clock; //gets me a timer

void Tester() {
	std::cout << "Begin vertex tests" << std::endl << std::endl;
	const int vecTestSize = 5000;
	glm::vec3 vectors[vecTestSize];

	//auto rotMatrix = glm::rotationMatrix(15.0, 25.0, 180.0);
	//auto transMatrix = glm ::mat4::createTranslationMatrix(cml::vec3f(10.0, -4.0, 25.0));
	//auto scaleMatrix = glm::mat4::createTranslationMatrix(cml::vec3f(0.12, 3.1, 2.5));
	//auto tranformationMatrix = rotMatrix * transMatrix * scaleMatrix;

	for (int i = 0; i < vecTestSize; i++)
	{
		vectors[i] = glm::vec3(rand() % 200 - 100, rand() % 200 - 100, rand() % 200 - 100);
		//std::cout << vectors[i] << std::endl;
	}

	std::cout << "Multiplying vectors by rotation matrix (15, 25, 180)" << std::endl;

	auto beginCount = Clock::now();
	for (int i = 0; i < vecTestSize; i++)
	{
		//tranformationMatrix.addScaleFactor(5);
		//tranformationMatrix.addTranslation(cml::vec3f(5, 5, 5));
		//vectors[i] = tranformationMatrix * vectors[i];
	}
	auto endCount = Clock::now();

	std::cout << "Time taken to compute " << vecTestSize << " vector multiplications is " << std::chrono::duration_cast<std::chrono::nanoseconds>(endCount - beginCount).count() << " nanoseconds" << std::endl;
	std::cout << "Time taken to compute " << vecTestSize << " vector multiplications is " << std::chrono::duration_cast<std::chrono::microseconds>(endCount - beginCount).count() << " microseconds" << std::endl;

	const int nrows = 100;
	const int ncols = 100;

	std::vector<float> terVerts;
	terVerts.resize(5 * ncols * nrows);
	int curPlace = 0;
	int data[nrows][ncols];

	for (int i = 0; i < nrows; i++) {
		for (int j = 0; j < ncols; j++) {
			data[i][j] = rand() % 100;
		}
	}

	beginCount = Clock::now();
	//subdiv verts
	for (int i = 0; i < nrows - 1; i++) {
		for (int j = 0; j < ncols - 1; j++) {
			terVerts[curPlace++] = 0.5 + i - nrows / 2;
			terVerts[curPlace++] = ((data[i][j] + data[i][j + 1] + data[i + 1][j] + data[i + 1][j + 1]) / 4);
			terVerts[curPlace++] = 0.5 + j - ncols / 2;

			terVerts[curPlace++] = 0.25*(i + 0.5f); //uv coord
			terVerts[curPlace++] = 0.25*(j + 0.5f); //uv coord
		}
	}
	endCount = Clock::now();

	std::cout << "Time taken to calculate " << nrows * ncols << " vertices is " << std::chrono::duration_cast<std::chrono::nanoseconds>(endCount - beginCount).count() << " nanoseconds" << std::endl;
	std::cout << "Time taken to calculate " << nrows * ncols << " vertices is " << std::chrono::duration_cast<std::chrono::microseconds>(endCount - beginCount).count() << " microseconds" << std::endl;

	//std::cout << "Press any key to continue..." << std::endl;
	//std::getchar();
}