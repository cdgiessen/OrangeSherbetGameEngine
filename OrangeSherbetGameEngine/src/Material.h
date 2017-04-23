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
	Material();
	Material(Texture* albedo);
	Material(Texture* albedo, Texture* specular);
	Material(Texture* albedo, Texture* specular, Texture* normal, Texture* emissive, Texture* height);
	~Material();

	glm::vec3 GetAmbient();
	void SetAmbient(glm::vec3 am);
	glm::vec3 GetDiffuse();
	void SetDiffuse(glm::vec3 diff);
	glm::vec3 GetSpecular();
	void SetSpecular(glm::vec3 spec);
	glm::vec3 GetTransmittance();
	void SetTransmittance(glm::vec3 tr);
	glm::vec3 GetEmission();
	void SetEmission(glm::vec3 em);
	float GetShininess();
	void SetShininess(float shine);

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
	void SetPropertiesToDefault();

	Shader* shader;

	Texture *t_albedo;
	Texture *t_specular;
	Texture *t_normal;
	Texture *t_emissive;
	Texture *t_height;

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