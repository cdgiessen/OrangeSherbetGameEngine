#include "Material.h"

Material::Material(Texture* albedo, Texture* specularT, Texture* normal, Texture* emissive, Texture* height) : t_albedo(albedo), t_specular(specularT), t_normal(normal), t_emissive(emissive), t_height(height)
{
	SetPropertiesToDefault();
}

Material::Material(Texture* albedo, Texture* specularT) : t_albedo(albedo), t_specular(specularT), t_normal(nullptr), t_emissive(nullptr), t_height(nullptr)
{
	SetPropertiesToDefault();
}

Material::Material(Texture* albedo) : t_albedo(albedo), t_specular(nullptr), t_normal(nullptr), t_emissive(nullptr), t_height(nullptr)
{
	SetPropertiesToDefault();
}

void Material::SetPropertiesToDefault() {
	ambient = glm::vec3(0.0f, 0.0f, 0.0f);
	diffuse = glm::vec3(0.9f, 0.9f, 0.9f);
	specular = glm::vec3(0.5f, 0.5f, 0.5f);
	shininess = 256.0f;
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

float Material::GetShininess() {
	return shininess;
}

Texture* Material::GetAlbedoTexture() {
	return t_albedo;
}

void Material::SetAlbedoTexture(Texture * albedo)
{
	albedo = albedo;
}

Texture* Material::GetSpecularTexture() {
	return t_specular;
}

void Material::SetSpecularTexture(Texture * specular)
{
	specular = specular;
}

Texture* Material::GetNormalTexture() {
	return t_normal;
}

void Material::SetNormalTexture(Texture * normal)
{
	normal = normal;
}

Texture* Material::GetEmissiveTexture() {
	return t_emissive;
}

void Material::SetEmissiveTexture(Texture * emissive)
{
	emissive = emissive;
}

Texture * Material::GetHeightTexture()
{
	return t_height;
}

void Material::SetHeightTexture(Texture * height) {
	height = height;
}

Shader* Material::GetShader() {
	return shader;
}
