#pragma once
#include <GLEW/glew.h>

class indexBuffer
{
private:
    unsigned int x_indexBufferId;
public:
    indexBuffer();
    ~indexBuffer();
public:
    unsigned int getindexBufferId();
    void bindindexBuffer();
    void unBindindexBuffer();
    void bindBufferData(GLsizeiptr size, const void* data);

};