#pragma once

#include <string>

#include <gl/glew.h>

class Texture
{
public:
	Texture(std::string filename, int w, int h);
	~Texture();

	GLuint GetTextureID();
	void Bind();

private:
	GLuint textureID;
};


