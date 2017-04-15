#include "Material.h"

Material::Material(Texture* albedo, Texture* specular, Texture* normal, Texture* emissive, Texture* height) : albedoTex(albedo), specularTex(specular), normalTex(normal), emissiveTex(emissive), heightTex(height)
{
}

Material::Material(Texture* albedo, Texture* specular) : albedoTex(albedo), specularTex(specular), normalTex(nullptr), emissiveTex(nullptr), heightTex(nullptr)
{
}

Material::Material(Texture* albedo) : albedoTex(albedo), specularTex(nullptr), normalTex(nullptr), emissiveTex(nullptr), heightTex(nullptr)
{
}

Material::~Material()
{
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
