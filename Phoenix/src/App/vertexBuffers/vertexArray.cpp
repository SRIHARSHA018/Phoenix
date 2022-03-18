#include "vertexArray.h"


vertexArray::vertexArray(unsigned int arrayCount):x_attributeCount(0),x_stride(0)
{
	glGenVertexArrays(arrayCount, &this->x_vertexArrayId);
}

vertexArray::~vertexArray()
{
	glDeleteVertexArrays(1, &this->x_vertexArrayId);
}

unsigned int vertexArray::getAttributeCount()
{
	return this->x_attributeCount;
}

unsigned int vertexArray::getVertexArrayId()
{
	return this->x_vertexArrayId;
}

void vertexArray::bindVertexArray()
{
	glBindVertexArray(this->x_vertexArrayId);
}

void vertexArray::unbindVertexArray()
{
	glBindVertexArray(0);
}

void vertexArray::pushBufferLayout(BufferLayout layout)
{
	this->x_layouts.emplace_back(layout);
	this->x_stride += layout.numElements * BufferLayout::getTypeSize(layout.type);
	this->x_attributeCount += 1;
}

void vertexArray::setupAndEnableAttributes()
{
	unsigned int offset =0;
	for (unsigned int i = 0; i < x_layouts.size(); i++) 
	{
		const auto& layout = x_layouts[i];
		glEnableVertexAttribArray(i);
		if (GL_INT == layout.type) {
			glVertexAttribIPointer(i, layout.numElements, layout.type, this->x_stride, (void*)offset);
		}
		else {
			glVertexAttribPointer(i,layout.numElements , layout.type, layout.normalized,this->x_stride , (void*)offset);
		}
		offset += layout.numElements * BufferLayout::getTypeSize(layout.type);
	}
	this->x_layouts.clear();
}
