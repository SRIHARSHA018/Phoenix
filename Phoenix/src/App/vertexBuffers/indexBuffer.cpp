#include "IndexBuffer.h"
IndexBuffer::IndexBuffer()
{
	glGenBuffers(1, &this->x_index_buffer_id);
}


IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &this->x_index_buffer_id);
}

unsigned int IndexBuffer::getindexBufferId()
{
	return this->x_index_buffer_id;
}

void IndexBuffer::bindindexBuffer()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->x_index_buffer_id);
}

void IndexBuffer::unBindindexBuffer()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->x_index_buffer_id);
}

void IndexBuffer::bindBufferData(GLsizeiptr size, const void* data)
{
	bindindexBuffer();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

}
