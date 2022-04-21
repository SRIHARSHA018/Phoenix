#pragma once
#include <GLEW/glew.h>

class IndexBuffer
{
private:
	unsigned int x_index_buffer_id;
public:
	IndexBuffer();
	~IndexBuffer();
public:
	unsigned int getindexBufferId();
	void bindindexBuffer();
	void unBindindexBuffer();
	void bindBufferData(GLsizeiptr size, const void* data);

};