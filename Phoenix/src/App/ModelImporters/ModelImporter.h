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

class ModelImporter
{
public:
	ModelImporter(const char* filepath);
	~ModelImporter();

public:
	void draw(unsigned int shaderProgramId);

private:
	void x_loadModel(const char* filepath);
	void x_processNode(aiNode* node,const aiScene* scene);
	Mesh* x_processMesh(aiMesh* mesh,const aiScene* scene);
	std::vector<Texture> x_loadMaterialTextures(aiMaterial* material, aiTextureType type,std::string typename);

private:
	std::string x_directory;

public:
	std::vector<Mesh*> meshes;
	std::vector<Texture> textures_loaded;

};


