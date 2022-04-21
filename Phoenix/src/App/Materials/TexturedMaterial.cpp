#include "TexturedMaterial.h"


TexturedMaterial::TexturedMaterial(unsigned int shader_program_id)
	:x_shader_program_id(shader_program_id)
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

void TexturedMaterial::setDiffuseTextureMap(const char* texture_path)
{

	x_diffuse->id = TextureFactory::createTextureUnit(texture_path);
	x_diffuse->path = texture_path;
	x_diffuse->type = "diffuse";
}

void TexturedMaterial::setSpecularTextureMap(const char* texture_path)
{

	x_specular->id = TextureFactory::createTextureUnit(texture_path);
	x_specular->path = texture_path;
	x_specular->type = "specular";
}

void TexturedMaterial::setDiffuseTextureMap(const Texture& diffuse_map)
{
	this->x_diffuse->id = diffuse_map.id;
	this->x_diffuse->path = diffuse_map.path;
	this->x_diffuse->type = diffuse_map.type;
}

void TexturedMaterial::setSpecularTextureMap(const Texture& texture_path)
{
	x_specular->id = texture_path.id;
	x_specular->path = texture_path.path;
	x_specular->type = texture_path.type;
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
	UniformManager::get()->setUniform("u_material.diffuse", this->x_shader_program_id, 0);
	UniformManager::get()->setUniform("u_material.specular", this->x_shader_program_id, 1);
	UniformManager::get()->setUniform("u_material.shininess", this->x_shader_program_id, this->x_shininess);
}
