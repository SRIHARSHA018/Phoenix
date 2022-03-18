#include "indexBuffer.h"
indexBuffer::indexBuffer()
{
    glGenBuffers(1, &this->x_indexBufferId);
}


indexBuffer::~indexBuffer()
{
    glDeleteBuffers(1, &this->x_indexBufferId);
}

unsigned int indexBuffer::getindexBufferId()
{
    return this->x_indexBufferId;
}

void indexBuffer::bindindexBuffer()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->x_indexBufferId);
}

void indexBuffer::unBindindexBuffer()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->x_indexBufferId);
}

void indexBuffer::bindBufferData(GLsizeiptr size, const void* data)
{
    bindindexBuffer();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,size, data, GL_STATIC_DRAW);

}
