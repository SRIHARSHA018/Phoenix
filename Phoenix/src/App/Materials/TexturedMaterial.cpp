#include "TexturedMaterial.h"


TexturedMaterial::TexturedMaterial(unsigned int shaderProgramId) :x_shaderProgramId(shaderProgramId)
{
	this->x_shininess = 0.f;
	x_diffuse = new Texture();
	x_specular = new Texture();
}

TexturedMaterial::~TexturedMaterial()
{
	if (x_diffuse != NULL) delete x_diffuse;
	if (x_specular != NULL) delete x_specular;

}

void TexturedMaterial::setDiffuseTextureMap(const char* texturePath)
{

	x_diffuse->id = TextureFactory::createTextureUnit(texturePath);
	x_diffuse->path = texturePath;
	x_diffuse->type = "diffuse";
}

void TexturedMaterial::setSpecularTextureMap(const char* texturePath)
{

	x_specular->id = TextureFactory::createTextureUnit(texturePath);
	x_specular->path = texturePath;
	x_specular->type = "specular";
}

void TexturedMaterial::setDiffuseTextureMap(const Texture& diffuseMap)
{
	this->x_diffuse->id = diffuseMap.id;
	this->x_diffuse->path = diffuseMap.path;
	this->x_diffuse->type = diffuseMap.type;
}

void TexturedMaterial::setSpecularTextureMap(const Texture& texturePath)
{
	x_specular->id = texturePath.id;
	x_specular->path = texturePath.path;
	x_specular->type = texturePath.type;
}

void TexturedMaterial::setShininess(float value)
{
	this->x_shininess = value;
}

void TexturedMaterial::bindMaterial()
{
	this->x_diffuse->bind(0);
	this->x_specular->bind(1);
}


void TexturedMaterial::update()
{
	this->x_updateUniforms();
}

MaterialType TexturedMaterial::getMaterialType()
{
	return MaterialType::TEXTURED_MATERIAL;
}

void TexturedMaterial::x_updateUniforms()
{
	UniformManager::get()->setUniform("u_material.diffuse", this->x_shaderProgramId, 0);
	UniformManager::get()->setUniform("u_material.specular", this->x_shaderProgramId, 1);
	UniformManager::get()->setUniform("u_material.shininess", this->x_shaderProgramId, this->x_shininess);
}
