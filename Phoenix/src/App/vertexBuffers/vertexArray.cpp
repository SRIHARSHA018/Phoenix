#include "VertexArray.h"


VertexArray::VertexArray(unsigned int array_count) :x_attribute_count(0), x_stride(0)
{
	glGenVertexArrays(array_count, &this->x_vertex_array_id);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &this->x_vertex_array_id);
}

unsigned int VertexArray::getAttributeCount()
{
	return this->x_attribute_count;
}

unsigned int VertexArray::getVertexArrayId()
{
	return this->x_vertex_array_id;
}

void VertexArray::bindVertexArray()
{
	glBindVertexArray(this->x_vertex_array_id);
}

void VertexArray::unbindVertexArray()
{
	glBindVertexArray(0);
}

void VertexArray::pushBufferLayout(BufferLayout layout)
{
	this->x_layouts.emplace_back(layout);
	this->x_stride += layout.num_elements * BufferLayout::getTypeSize(layout.type);
	this->x_attribute_count += 1;
}

void VertexArray::setupAndEnableAttributes()
{
	unsigned int offset = 0;
	for (unsigned int i = 0; i < x_layouts.size(); i++)
	{
		const auto& layout = x_layouts[i];
		glEnableVertexAttribArray(i);
		if (GL_INT == layout.type) {
			glVertexAttribIPointer(i, layout.num_elements, layout.type, this->x_stride, (void*)offset);
		}
		else {
			glVertexAttribPointer(i, layout.num_elements, layout.type, layout.normalized, this->x_stride, (void*)offset);
		}
		offset += layout.num_elements * BufferLayout::getTypeSize(layout.type);
	}
	this->x_layouts.clear();
}
