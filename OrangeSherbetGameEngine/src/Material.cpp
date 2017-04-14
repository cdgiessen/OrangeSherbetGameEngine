#include "Material.h"

Material::Material(Texture* albedo) : albedoTex(albedo)
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
