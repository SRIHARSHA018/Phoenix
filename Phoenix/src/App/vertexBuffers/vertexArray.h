#pragma once

#include <GLEW/glew.h>
#include <vector>
struct BufferLayout 
{
	unsigned int numElements;
	unsigned int type;
	bool normalized;
	static unsigned int getTypeSize(unsigned int type) {
		switch (type)
		{
		case GL_FLOAT:			return sizeof(GL_FLOAT);
		case GL_UNSIGNED_INT:	return sizeof(GL_UNSIGNED_INT);
		case GL_UNSIGNED_BYTE:	return sizeof(GL_UNSIGNED_BYTE);
		case GL_INT:			return sizeof(GL_INT);
		default:
			break;
		}
	}
};

class vertexArray
{
private:
	unsigned int x_vertexArrayId;
	unsigned int x_attributeCount;
	unsigned int x_stride;
	std::vector<BufferLayout> x_layouts;

public:
	vertexArray(unsigned int arrayCount =1);
	~vertexArray();

public:
	unsigned int getAttributeCount();
	unsigned int getVertexArrayId();
	void bindVertexArray();
	void unbindVertexArray();

	void pushBufferLayout(BufferLayout layout);
	void setupAndEnableAttributes();
};

