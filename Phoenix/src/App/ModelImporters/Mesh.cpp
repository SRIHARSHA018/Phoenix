#include "Mesh.h"
#include <iostream>


Mesh::~Mesh()
{

}
Mesh::Mesh()
{

}

void Mesh::draw(unsigned int shader_program_id)
{

	glUseProgram(shader_program_id);

	TexturedMaterial material(shader_program_id);
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		if (textures[i].type == "texture_diffuse")
			material.setDiffuseTextureMap(textures[i]);

		else if (textures[i].type == "texture_specular")
			material.setSpecularTextureMap(textures[i]);
	}
	material.setShininess(64.7);
	material.bindMaterial();
	material.update();

	vao.bindVertexArray();
	glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, (const void*)0);
	vao.unbindVertexArray();
}


void Mesh::setUpMesh()
{
	this->x_setupMesh();
}

void Mesh::x_setupMesh()
{
	vao.bindVertexArray();
	vbo.bindVertexBuffer();
	vbo.bindBufferData(this->vertices.size() * sizeof(Vertex), &this->vertices[0]);
	ibo.bindindexBuffer();
	ibo.bindBufferData(this->indices.size() * sizeof(unsigned int), &this->indices[0]);
	vao.pushBufferLayout({ 3,GL_FLOAT,GL_FALSE });
	vao.pushBufferLayout({ 2,GL_FLOAT,GL_FALSE });
	vao.pushBufferLayout({ 3,GL_FLOAT,GL_FALSE });
	//vao.pushBufferLayout({ 3,GL_FLOAT,GL_FALSE });
	//vao.pushBufferLayout({ 3,GL_FLOAT,GL_FALSE });
	//vao.pushBufferLayout({ 4,GL_INT,GL_FALSE });
	//vao.pushBufferLayout({ 4,GL_FLOAT,GL_FALSE });
	vao.setupAndEnableAttributes();
	vao.unbindVertexArray();

}

