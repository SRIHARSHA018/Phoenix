#pragma once
#include <GLEW/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>

#include "Materials/TexturedMaterial.h"
#include "vertexBuffers/vertexArray.h"
#include "vertexBuffers/vertexBuffer.h"
#include "vertexBuffers/indexBuffer.h"
#include "Shaders/UniformManager.h"

#define MAX_BONE_INFLUENCE 4

struct Vertex
{

	glm::vec3 Position;

	glm::vec2 TexCoords;

	glm::vec3 Normal;

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
	void draw(unsigned int shaderProgramId);
	std::string meshName;

public:
	std::vector<Vertex>       vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture>      textures;

	vertexArray vao;
	vertexBuffer vbo;
	indexBuffer ibo;

	unsigned int Vao, Vbo, Ibo;


public:
	void setUpMesh();
private:
	void x_setupMesh();
};

