#pragma once
#include<iostream>
#include<GLEW/glew.h>
#include "StbImage/stb_image.h"


struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
	void bind(unsigned int tex_slot) {
		glActiveTexture(GL_TEXTURE0 + tex_slot);
		glBindTexture(GL_TEXTURE_2D, this->id);
	}
	void unBind() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
};