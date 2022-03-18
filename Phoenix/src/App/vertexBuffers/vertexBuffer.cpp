#include "vertexbuffer.h"
vertexBuffer::vertexBuffer()
{
    glGenBuffers(1, &this->x_vertexBufferId);
}


vertexBuffer::~vertexBuffer()
{
    glDeleteBuffers(1, &this->x_vertexBufferId);
}

unsigned int vertexBuffer::getVertexBufferId()
{
    return this->x_vertexBufferId;
}

void vertexBuffer::bindVertexBuffer()
{
    glBindBuffer(GL_ARRAY_BUFFER, this->x_vertexBufferId);
}

void vertexBuffer::unBindVertexBuffer()
{
    glBindBuffer(GL_ARRAY_BUFFER, this->x_vertexBufferId);
}

void vertexBuffer::bindBufferData(GLsizeiptr size, const void* data)
{
    bindVertexBuffer();
    glBufferData(GL_ARRAY_BUFFER,size, data, GL_STATIC_DRAW);

}
