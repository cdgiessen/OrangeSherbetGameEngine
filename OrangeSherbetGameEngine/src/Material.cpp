#include "Material.h"

Material::Material(Texture* albedo, Texture* specularT, Texture* normal, Texture* emissive, Texture* height) : albedoTex(albedo), specularTex(specularT), normalTex(normal), emissiveTex(emissive), heightTex(height)
{
	ambient = glm::vec3(0.0f, 0.0f, 0.0f);
	diffuse = glm::vec3(0.9f, 0.9f, 0.9f);
	specular = glm::vec3(0.2f, 0.2f, 0.2f);
}

Material::Material(Texture* albedo, Texture* specularT) : albedoTex(albedo), specularTex(specularT), normalTex(nullptr), emissiveTex(nullptr), heightTex(nullptr)
{
	ambient = glm::vec3(0.0f, 0.0f, 0.0f);
	diffuse = glm::vec3(0.9f, 0.9f, 0.9f);
	specular = glm::vec3(0.2f, 0.2f, 0.2f);
}

Material::Material(Texture* albedo) : albedoTex(albedo), specularTex(nullptr), normalTex(nullptr), emissiveTex(nullptr), heightTex(nullptr)
{
	ambient = glm::vec3(0.0f, 0.0f, 0.0f);
	diffuse = glm::vec3(0.9f, 0.9f, 0.9f);
	specular = glm::vec3(0.2f, 0.2f, 0.2f);
}

Material::~Material()
{
}

glm::vec3 Material::GetAmbient()
{
	return ambient;
}

glm::vec3 Material::GetDiffuse()
{
	return diffuse;
}

glm::vec3 Material::GetSpecular()
{
	return specular;
}

glm::vec3 Material::GetTransmittance()
{
	return transmittance;
}

glm::vec3 Material::GetEmission()
{
	return emission;
}

Texture* Material::GetAlbedoTexture() {
	return albedoTex;
}

void Material::SetAlbedoTexture(Texture * albedo)
{
	albedoTex = albedo;
}

Texture* Material::GetSpecularTexture() {
	return specularTex;
}

void Material::SetSpecularTexture(Texture * specular)
{
	specularTex = specular;
}

Texture* Material::GetNormalTexture() {
	return normalTex;
}

void Material::SetNormalTexture(Texture * normal)
{
	normalTex = normal;
}

Texture* Material::GetEmissiveTexture() {
	return emissiveTex;
}

void Material::SetEmissiveTexture(Texture * emissive)
{
	emissiveTex = emissive;
}

Texture * Material::GetHeightTexture()
{
	return heightTex;
}

void Material::SetHeightTexture(Texture * height) {
	heightTex = height;
}

Shader* Material::GetShader() {
	return shader;
}
