#pragma once

enum class MaterialType {
	STANDARD_MATERIAL,
	TEXTURED_MATERIAL,
	PBR_MATERIAL
};

class IMaterial 
{
public:
	virtual ~IMaterial() = default;
public:
	virtual void update() = 0;
	virtual MaterialType getMaterialType() = 0;
};