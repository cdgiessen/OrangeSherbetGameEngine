#pragma once

#include <string>

#include <gl/glew.h>

enum TextureType {
	Albedo = 0,
	Diffuse = 1,
	Specular = 2,
	Normal = 3,
	Height = 4,
};

class Texture
{
public:
	Texture(std::string filename, int w, int h, TextureType type);
	~Texture();

	GLuint GetTextureID();
	TextureType GetTextureType();
	void Bind();

private:
	GLuint textureID;

	TextureType type;
};


