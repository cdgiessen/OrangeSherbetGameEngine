#pragma once

#include "../include/Texture.h"

#include "stb_image.h"

Texture::Texture(std::string filename, int w, int h, TextureType type) : type(type){

	int comp;

	unsigned char* image = stbi_load(filename.c_str(), &w, &h, &comp, STBI_rgb);

	if (image == nullptr)
		throw(std::string("Failed to load texture"));

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(image);
}

Texture::~Texture() {

}

GLuint Texture::GetTextureID() {
	return textureID;
}

TextureType Texture::GetTextureType() {
	return type;
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}

