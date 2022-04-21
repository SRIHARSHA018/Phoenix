#pragma once
#include <GLEW/glew.h>
//new layout
class VertexBuffer
{
private:
	unsigned int x_vertex_buffer_id;
public:
	VertexBuffer();
	~VertexBuffer();
public:
	unsigned int getVertexBufferId();
	void bindVertexBuffer();
	void unBindVertexBuffer();
	void bindBufferData(GLsizeiptr size, const void* data);

};