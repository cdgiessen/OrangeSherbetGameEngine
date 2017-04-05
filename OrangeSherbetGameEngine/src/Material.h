#pragma once

#ifndef MATERIAL_H
#define MATERIAL_H

#include "Texture.h"
#include "Shader.h"

#include <CML\vec3.h>

class Material
{
public:
	Material(Texture* albedo);
	~Material();

	Texture* GetAlbedoTexture();
	Texture* GetSpecularTexture();
	Texture* GetNormalTexture();
	Texture* GetEmissiveTexture();
	Shader* GetShader();

	Shader* shader;

	Texture *albedoTex;
	Texture *specularTex;
	Texture *normalTex;
	Texture *emissiveTex;

	cml::vec3f ambient;
	cml::vec3f diffuse;
	cml::vec3f specular;
	cml::vec3f transmittance;
	cml::vec3f emission;
	float shininess;
	float ior;       // index of refraction
	float dissolve;  // 1 == opaque; 0 == fully transparent
					 // illumination model (see http://www.fileformat.info/format/material/)
	int illum;

};

#endif //MATERIAL_H