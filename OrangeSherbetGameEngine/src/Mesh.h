#pragma once

#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL\glew.h>
#include <CML\cml.h>

#include "Shader.h"
#include "Material.h"

//#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

struct Vertex {
	cml::vec3f Position; // Position
	cml::vec3f Normal; // Normal
	cml::vec2f TexCoords; // TexCoords

	Vertex(cml::vec3f pos, cml::vec3f norm, cml::vec2f tex) {
		Position = pos;
		Normal = norm;
		TexCoords = tex;
	}

	Vertex() : Position(cml::VEC3_ZERO), Normal(cml::VEC3_ZERO), TexCoords(cml::vec2f(0,0)) {}
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