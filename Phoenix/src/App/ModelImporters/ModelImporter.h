#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Mesh.h"
#include "TextureUnit/Texture.h"
#include "TextureUnit/TextureFactory.h"
#include "SceneObject.h"
#include "UniformManager.h"

class ModelImporter:public ISceneObject
{
public:
	ModelImporter(const char* filepath,unsigned int shaderProgramId);
	~ModelImporter();

public:
	virtual void update() override;
	virtual void onEvent(IEvent& event);

private:
	void x_loadModel(const char* filepath);
	void x_processNode(aiNode* node,const aiScene* scene);
	void x_updateUniforms();
	void x_draw();
	glm::mat4 x_getModelMatrix();
	Mesh* x_processMesh(aiMesh* mesh,const aiScene* scene);
	std::vector<Texture> x_loadMaterialTextures(aiMaterial* material, aiTextureType type,std::string typename);

private:
	std::string x_directory;
	unsigned int x_shaderProgramId;

public:
	std::vector<Mesh*> meshes;
	std::vector<Texture> textures_loaded;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};


