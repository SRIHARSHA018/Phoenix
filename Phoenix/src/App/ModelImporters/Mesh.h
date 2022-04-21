#pragma once
#include <GLEW/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>

#include "Materials/TexturedMaterial.h"
#include "VertexBuffers/VertexArray.h"
#include "VertexBuffers/VertexBuffer.h"
#include "VertexBuffers/IndexBuffer.h"
#include "Shaders/UniformManager.h"

#define MAX_BONE_INFLUENCE 4

struct Vertex
{

	glm::vec3 position;

	glm::vec2 tex_coords;

	glm::vec3 normal;

	//glm::vec3 Tangent;

	//glm::vec3 Bitangent;

	//int m_BoneIDs[MAX_BONE_INFLUENCE];

	//float m_Weights[MAX_BONE_INFLUENCE];
};

class Mesh
{
public:
	Mesh();
	~Mesh();
public:
	void draw(unsigned int shader_program_id);
	std::string mesh_name;

public:
	std::vector<Vertex>       vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture>      textures;

	VertexArray vao;
	VertexBuffer vbo;
	IndexBuffer ibo;

	unsigned int Vao, Vbo, Ibo;


public:
	void setUpMesh();
private:
	void x_setupMesh();
};

