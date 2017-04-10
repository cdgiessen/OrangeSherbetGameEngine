#pragma once

#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL\glew.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
//#include <CML\cml.h>

#include "Shader.h"
#include "Material.h"

//#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

struct Vertex {
	glm::vec3 Position; // Position
	glm::vec3 Normal; // Normal
	glm::vec2 TexCoords; // TexCoords

	Vertex(glm::vec3 pos, glm::vec3 norm, glm::vec2 tex) {
		Position = pos;
		Normal = norm;
		TexCoords = tex;
	}

	Vertex() : Position(glm::vec3(0.0f,0.0f,0.0f)), Normal(glm::vec3(0.0f, 0.0f, 0.0f)), TexCoords(glm::vec2(0.0f, 0.0f)) {}
};

class Mesh {
public:
	//Determines if the mesh is vertex array only, or vertexes with indicy array.
	//Most meshes will be 1, but primitives (like cube) are zero
	enum VertexBufferIndicyType {
		VertexArrayOnly = 0,
		VertexAndIndicy = 1
	};

	//Constructor for meshes with vertex and indicy arrays
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, Material* materials);

	//Constructor for meshes with only a vertex array
	Mesh(std::vector<Vertex> vertices, Material* materials);

	void Draw(Shader shader); // Render the mesh

	void setupMesh(); // Initializes all the buffer objects/arrays


	VertexBufferIndicyType meshVertexArrayType;
	

	/*  Render data  */
	GLuint VAO, VBO, EBO;

	/*  Mesh Data  */
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	Material* material;
};
#endif // !MESH_H
