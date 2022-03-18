#pragma once
#include "IMaterial.h"


class StandardMaterial :public IMaterial
{
public:
	StandardMaterial();
	~StandardMaterial();
public:
	virtual void update();
	virtual MaterialType getMaterialType() override;
private:
	void x_updateUniforms();
};