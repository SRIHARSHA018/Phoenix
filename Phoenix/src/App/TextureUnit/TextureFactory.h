#pragma once
#include <GLEW/glew.h>
#include <iostream>

#include "StbImage/stb_image.h"

class TextureFactory {
public:
	static unsigned int createTextureUnit(const char* textureFilePath);
};
