#pragma once

#ifndef MATERIAL_H
#define MATERIAL_H

#include "Texture.h"
#include "Shader.h"

//#include <CML\vec3.h>
#include <glm/vec3.hpp>

class Material
{
public:
	Material(Texture* albedo);
	~Material();

	Texture* GetAlbedoTexture();
	void SetAlbedoTexture(Texture * albedo);

	Texture* GetSpecularTexture();
	void SetSpecularTexture(Texture * specular);

	Texture* GetNormalTexture();
	void SetNormalTexture(Texture * normal);

	Texture* GetEmissiveTexture();
	void SetEmissiveTexture(Texture * emissive);

	Texture* GetHeightTexture();
	void SetHeightTexture(Texture * height);

	Shader* GetShader();

private:
	Shader* shader;

	Texture *albedoTex;
	Texture *specularTex;
	Texture *normalTex;
	Texture *emissiveTex;
	Texture *heightTex;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 transmittance;
	glm::vec3 emission;

	float shininess;
	float ior;       // index of refraction
	float dissolve;  // 1 == opaque; 0 == fully transparent
					 // illumination model (see http://www.fileformat.info/format/material/)
	int illum;

};

#endif //MATERIAL_H