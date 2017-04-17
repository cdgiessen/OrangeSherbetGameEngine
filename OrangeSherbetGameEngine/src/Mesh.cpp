#include "Mesh.h"

Mesh* LoadMesh(std::string inputfile, Material* mat) {


	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string cerr;
	bool cret = tinyobj::LoadObj(&attrib, &shapes, &materials, &cerr, inputfile.c_str());

	if (!cerr.empty()) { // `err` may contain warning message.
		std::cerr << cerr << std::endl;
	}

	if (!cret) {
		exit(1);
	}

	std::unordered_map<Vertex, int> uniqueVertices = {};
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	for (const auto& shape : shapes) {
		for (const auto& index : shape.mesh.indices) {
			Vertex vertex = {};

			vertex.Position = {
				attrib.vertices[3 * index.vertex_index + 0],
				attrib.vertices[3 * index.vertex_index + 1],
				attrib.vertices[3 * index.vertex_index + 2]
			};

			vertex.TexCoords = {
				attrib.texcoords[2 * index.texcoord_index + 0],
				1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
			};

			vertex.Normal = {
				attrib.vertices[3 * index.normal_index + 0],
				attrib.vertices[3 * index.normal_index + 1],
				attrib.vertices[3 * index.normal_index + 2]
			};

			if (uniqueVertices.count(vertex) == 0) {
				uniqueVertices[vertex] = vertices.size();
				vertices.push_back(vertex);
			}

			indices.push_back(uniqueVertices[vertex]);
		}
	}
	
	return new Mesh(vertices, indices, mat);
}

Mesh* LoadCubeMesh(Material* mat) {
	std::vector<Vertex> vertices;

	vertices.push_back(Vertex(glm::vec3(	0.5f, -0.5f, -0.5f		), glm::vec3(0.0f, 0.0f, -1.0f),	glm::vec2( 0.0f, 1.0f)));
	vertices.push_back(Vertex(glm::vec3(	-0.5f, -0.5f, -0.5f		), glm::vec3(0.0f, 0.0f, -1.0f),	glm::vec2( 1.0f, 1.0f)));
	vertices.push_back(Vertex(glm::vec3(	0.5f, 0.5f, -0.5f		), glm::vec3(0.0f, 0.0f, -1.0f),	glm::vec2( 0.0f, 0.0f)));
	vertices.push_back(Vertex(glm::vec3(	-0.5f, 0.5f, -0.5f		), glm::vec3(0.0f, 0.0f, -1.0f),	glm::vec2( 1.0f, 0.0f)));
	vertices.push_back(Vertex(glm::vec3(	0.5f, 0.5f, -0.5f		), glm::vec3(0.0f, 0.0f, -1.0f),	glm::vec2( 0.0f, 0.0f)));
	vertices.push_back(Vertex(glm::vec3(	-0.5f, -0.5f, -0.5f		), glm::vec3(0.0f, 0.0f, -1.0f),	glm::vec2( 1.0f, 1.0f)));
																												  				 
	//Right face																								  				  
	vertices.push_back(Vertex(glm::vec3(	0.5f, 0.5f, 0.5f		), glm::vec3(0.0f, 0.0f, 1.0f),		glm::vec2 (1.0f, 0.0f	)));
	vertices.push_back(Vertex(glm::vec3(	-0.5f, -0.5f, 0.5f		), glm::vec3(0.0f, 0.0f, 1.0f),		glm::vec2 (0.0f, 1.0f	)));
	vertices.push_back(Vertex(glm::vec3(	0.5f, -0.5f, 0.5f		), glm::vec3(0.0f, 0.0f, 1.0f),		glm::vec2 (1.0f, 1.0f	)));
	vertices.push_back(Vertex(glm::vec3(	0.5f, 0.5f, 0.5f		), glm::vec3(0.0f, 0.0f, 1.0f),		glm::vec2 (1.0f, 0.0f	)));
	vertices.push_back(Vertex(glm::vec3(	-0.5f, 0.5f, 0.5f		), glm::vec3(0.0f, 0.0f, 1.0f),		glm::vec2 (0.0f, 0.0f	)));
	vertices.push_back(Vertex(glm::vec3(	-0.5f, -0.5f, 0.5f		), glm::vec3(0.0f, 0.0f, 1.0f),		glm::vec2 (0.0f, 1.0f	)));
																												  				  
	//Back face																									  				  
	vertices.push_back(Vertex(glm::vec3(	-0.5f, -0.5f, -0.5f		), glm::vec3(-1.0f, 0.0f, 0.0f),	glm::vec2( 0.0f, 1.0f	)));
	vertices.push_back(Vertex(glm::vec3(	-0.5f, -0.5f, 0.5f		), glm::vec3(-1.0f, 0.0f, 0.0f),	glm::vec2( 1.0f, 1.0f)));
	vertices.push_back(Vertex(glm::vec3(	-0.5f, 0.5f, 0.5f		), glm::vec3(-1.0f, 0.0f, 0.0f),	glm::vec2( 1.0f, 0.0f)));
	vertices.push_back(Vertex(glm::vec3(	-0.5f, 0.5f, 0.5f		), glm::vec3(-1.0f, 0.0f, 0.0f),	glm::vec2( 1.0f, 0.0f)));
	vertices.push_back(Vertex(glm::vec3(	-0.5f, 0.5f, -0.5f		), glm::vec3(-1.0f, 0.0f, 0.0f),	glm::vec2( 0.0f, 0.0f	)));
	vertices.push_back(Vertex(glm::vec3(	-0.5f, -0.5f, -0.5f		), glm::vec3(-1.0f, 0.0f, 0.0f),	glm::vec2( 0.0f, 1.0f	)));
																																  
	//Front face																												  
	vertices.push_back(Vertex(glm::vec3(	0.5f, 0.5f, -0.5f		), glm::vec3(1.0f, 0.0f, 0.0f),		glm::vec2( 1.0f, 0.0f	)));
	vertices.push_back(Vertex(glm::vec3(	0.5f, 0.5f, 0.5f		), glm::vec3(1.0f, 0.0f, 0.0f),		glm::vec2( 0.0f, 0.0f	)));
	vertices.push_back(Vertex(glm::vec3(	0.5f, -0.5f, -0.5f		), glm::vec3(1.0f, 0.0f, 0.0f),		glm::vec2( 1.0f, 1.0f	)));
	vertices.push_back(Vertex(glm::vec3(	0.5f, -0.5f, 0.5f		), glm::vec3(1.0f, 0.0f, 0.0f),		glm::vec2( 0.0f, 1.0f	)));
	vertices.push_back(Vertex(glm::vec3(	0.5f, -0.5f, -0.5f		), glm::vec3(1.0f, 0.0f, 0.0f),		glm::vec2( 1.0f, 1.0f	)));
	vertices.push_back(Vertex(glm::vec3(	0.5f, 0.5f, 0.5f		), glm::vec3(1.0f, 0.0f, 0.0f),		glm::vec2( 0.0f, 0.0f	)));
																																  
	//Bottom face																												  
	vertices.push_back(Vertex(glm::vec3(	0.5f, -0.5f, 0.5f		), glm::vec3(0.0f, -1.0f, 0.0f),	glm::vec2( 0.0f, 0.0f)));
	vertices.push_back(Vertex(glm::vec3(	-0.5f, -0.5f, -0.5f		), glm::vec3(0.0f, -1.0f, 0.0f),	glm::vec2( 1.0f, 1.0f	)));
	vertices.push_back(Vertex(glm::vec3(	0.5f, -0.5f, -0.5f		), glm::vec3(0.0f, -1.0f, 0.0f),	glm::vec2( 0.0f, 1.0f)));
	vertices.push_back(Vertex(glm::vec3(	0.5f, -0.5f, 0.5f		), glm::vec3(0.0f, -1.0f, 0.0f),	glm::vec2( 0.0f, 0.0f)));
	vertices.push_back(Vertex(glm::vec3(	-0.5f, -0.5f, 0.5f		), glm::vec3(0.0f, -1.0f, 0.0f),	glm::vec2( 1.0f, 0.0f	)));
	vertices.push_back(Vertex(glm::vec3(	-0.5f, -0.5f, -0.5f		), glm::vec3(0.0f, -1.0f, 0.0f),	glm::vec2( 1.0f, 1.0f	)));
																																  
	//Top face																													  
	vertices.push_back(Vertex(glm::vec3(	0.5f, 0.5f, -0.5f		), glm::vec3(0.0f, 1.0f, 0.0f),		glm::vec2( 1.0f, 1.0f	)));
	vertices.push_back(Vertex(glm::vec3(	-0.5f, 0.5f, -0.5f		), glm::vec3(0.0f, 1.0f, 0.0f),		glm::vec2( 0.0f, 1.0f	)));
	vertices.push_back(Vertex(glm::vec3(	0.5f, 0.5f, 0.5f		), glm::vec3(0.0f, 1.0f, 0.0f),		glm::vec2( 1.0f, 0.0f	)));
	vertices.push_back(Vertex(glm::vec3(	-0.5f, 0.5f, 0.5f		), glm::vec3(0.0f, 1.0f, 0.0f),		glm::vec2( 0.0f, 0.0f	)));
	vertices.push_back(Vertex(glm::vec3(	0.5f, 0.5f, 0.5f		), glm::vec3(0.0f, 1.0f, 0.0f),		glm::vec2( 1.0f, 0.0f	)));
	vertices.push_back(Vertex(glm::vec3(	-0.5f, 0.5f, -0.5f		), glm::vec3(0.0f, 1.0f, 0.0f),		glm::vec2( 0.0f, 1.0f	)));

	
	return new Mesh(vertices, mat);
}


Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, Material* material)
{
	this->vertices = vertices;
	this->indices = indices;
	this->material = material;

	this->meshVertexArrayType = Mesh::VertexBufferIndicyType::VertexAndIndicy;

	// Now that we have all the required data, set the vertex buffers and its attribute pointers.
	this->setupMesh();
}

Mesh::Mesh(std::vector<Vertex> vertices, Material* material)
{
	this->vertices = vertices;
	this->material = material;

	this->meshVertexArrayType = Mesh::VertexBufferIndicyType::VertexArrayOnly;

	// Now that we have all the required data, set the vertex buffers and its attribute pointers.
	this->setupMesh();
}

// Initializes all the buffer objects/arrays
void Mesh::setupMesh()
{
	// Create buffers/arrays
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	if (meshVertexArrayType == Mesh::VertexBufferIndicyType::VertexAndIndicy) {
		glGenBuffers(1, &this->EBO);
	}

	glBindVertexArray(this->VAO);
	// Load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	// A great thing about structs is that their memory layout is sequential for all its items.
	// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
	// again translates to 3/2 floats which translates to a byte array.
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

	if (meshVertexArrayType == Mesh::VertexBufferIndicyType::VertexAndIndicy) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);
	}

	// Set the vertex attribute pointers
	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	// Vertex Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
	// Vertex Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
}


// Render the mesh
void Mesh::Draw(GLSLProgram* shader)
{
	
		glActiveTexture(GL_TEXTURE0 + 0); // Active proper texture unit before binding
		// Retrieve texture number (the N in diffuse_textureN)
		//std::stringstream ss;
		//std::string name;
		//TextureType type = material->GetAlbedoTexture()->GetTextureType();
		//switch (type) {
		//case (0) :
		//	name = "t_albedo"; break;
		//case (1) :
		//	name = "t_diffuse"; break;
		//case (2) :
		//	name = "t_specular"; break;
		//case (3) :
		//	name = "t_normal"; break;
		//case (4) :
		//	name = "t_emmision"; break;
		//default : 
		//	std::cout << "ERROR :: Couldn't find appropriate case" << std::endl;
		//}
		//// Now set the sampler to the correct texture unit
		//glUniform1i(glGetUniformLocation(shader->getHandle(), (name).c_str()), 0);
		//// And finally bind the texture
		//glBindTexture(GL_TEXTURE_2D, material->GetAlbedoTexture()->GetTextureID());
	
	GLuint adsIndex = glGetSubroutineIndex(shader->getHandle(), GL_FRAGMENT_SHADER, "PointLightADS");
	GLuint adsNoSpecTexIndex = glGetSubroutineIndex(shader->getHandle(), GL_FRAGMENT_SHADER, "PointLightADSNoSpecTexture");

	glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &adsNoSpecTexIndex);

	if (material->GetAlbedoTexture() != nullptr) {
		glActiveTexture(GL_TEXTURE0 + 0);
		glUniform1i(glGetUniformLocation(shader->getHandle(), "t_albedo"), 0);
		glBindTexture(GL_TEXTURE_2D, material->GetAlbedoTexture()->GetTextureID());
	}
	if (material->GetSpecularTexture() != nullptr) {
		glActiveTexture(GL_TEXTURE0 + 1);
		glUniform1i(glGetUniformLocation(shader->getHandle(), "t_specular"), 1);
		glBindTexture(GL_TEXTURE_2D, material->GetSpecularTexture()->GetTextureID());

		glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &adsIndex);
	}
	if (material->GetNormalTexture() != nullptr) {
		glActiveTexture(GL_TEXTURE0 + 2);
		glUniform1i(glGetUniformLocation(shader->getHandle(), "t_normal"), 2);
		glBindTexture(GL_TEXTURE_2D, material->GetNormalTexture()->GetTextureID());
	}
	if (material->GetEmissiveTexture() != nullptr) {
		glActiveTexture(GL_TEXTURE0 + 3);
		glUniform1i(glGetUniformLocation(shader->getHandle(), "t_emmision"), 3);
		glBindTexture(GL_TEXTURE_2D, material->GetEmissiveTexture()->GetTextureID());
	}

	shader->setUniform("material.ambient", material->GetAmbient());
	shader->setUniform("material.diffuse", material->GetDiffuse());
	shader->setUniform("material.specular", material->GetSpecular());
	shader->setUniform("material.shininess", material->GetShininess());
	
	// Draw mesh
	glBindVertexArray(this->VAO);
	if (meshVertexArrayType == Mesh::VertexBufferIndicyType::VertexAndIndicy) {
		glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	}
	else {
		glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
	}
	glBindVertexArray(0);

	// Always good practice to set everything back to defaults once configured.
	
		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	
}

