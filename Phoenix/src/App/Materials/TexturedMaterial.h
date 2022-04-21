#pragma once
#include <string>
#include "IMaterial.h"
#include "TextureUnit/TextureFactory.h"
#include "TextureUnit/Texture.h"
#include "Shaders/UniformManager.h"

class TexturedMaterial :public IMaterial
{
public:
	TexturedMaterial(unsigned int shader_program_id);
	~TexturedMaterial();

public:
	void setDiffuseTextureMap(const char* texture_path);
	void setSpecularTextureMap(const char* texture_path);
	void setDiffuseTextureMap(const Texture& diffuse_map);
	void setSpecularTextureMap(const Texture& texture_path);
	void setShininess(float value);
	void bindMaterial();

public:
	virtual void update();
	virtual MaterialType getMaterialType() override;

private:
	void x_updateUniforms();
	unsigned int x_shader_program_id;
	Texture* x_diffuse;
	Texture* x_specular;
	float x_shininess;
};