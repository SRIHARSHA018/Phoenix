#pragma once
#include <GLEW/glew.h>
//new layout
class vertexBuffer
{
private:
    unsigned int x_vertexBufferId;
public:
    vertexBuffer();
    ~vertexBuffer();
public:
    unsigned int getVertexBufferId();
    void bindVertexBuffer();
    void unBindVertexBuffer();
    void bindBufferData(GLsizeiptr size, const void* data);

};