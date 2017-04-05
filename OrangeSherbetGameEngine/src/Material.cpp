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

Texture* Material::GetSpecularTexture() {
	return specularTex;
}

Texture* Material::GetNormalTexture() {
	return normalTex;
}

Texture* Material::GetEmissiveTexture() {
	return emissiveTex;
}

Shader* Material::GetShader() {
	return shader;
}
