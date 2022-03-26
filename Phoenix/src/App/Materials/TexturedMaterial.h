#pragma once
#include <string>
#include "IMaterial.h"
#include "TextureUnit/TextureFactory.h"
#include "TextureUnit/Texture.h"
#include "Shaders/UniformManager.h"

class TexturedMaterial :public IMaterial
{
public:
	TexturedMaterial(unsigned int shaderProgramId);
	~TexturedMaterial();

public:
	void setDiffuseTextureMap(const char* texturePath);
	void setSpecularTextureMap(const char* texturePath);
	void setDiffuseTextureMap(const Texture& diffuseMap);
	void setSpecularTextureMap(const Texture& texturePath);
	void setShininess(float value);
	void bindMaterial();

public:
	virtual void update();
	virtual MaterialType getMaterialType() override;

private:
	void x_updateUniforms();
	unsigned int x_shaderProgramId;
	Texture* x_diffuse;
	Texture* x_specular;
	float x_shininess;
};