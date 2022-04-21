#include "Vertexbuffer.h"
VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &this->x_vertex_buffer_id);
}


VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &this->x_vertex_buffer_id);
}

unsigned int VertexBuffer::getVertexBufferId()
{
	return this->x_vertex_buffer_id;
}

void VertexBuffer::bindVertexBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->x_vertex_buffer_id);
}

void VertexBuffer::unBindVertexBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->x_vertex_buffer_id);
}

void VertexBuffer::bindBufferData(GLsizeiptr size, const void* data)
{
	bindVertexBuffer();
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

}
