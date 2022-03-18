#include "ModelImporter.h"

ModelImporter::ModelImporter(const char* filepath)
{
	this->x_loadModel(filepath);
}

ModelImporter::~ModelImporter()
{
	for (unsigned int i = 0; i < meshes.size(); i++) {
		delete meshes[i];
	}
}

void ModelImporter::draw(unsigned int shaderProgramId)
{
	for (unsigned int i = 0; i < meshes.size(); i++) 
	{
		meshes[i]->draw(shaderProgramId);
	}
}

void ModelImporter::x_loadModel(const char* filepath)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_OptimizeMeshes);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}
	
	this->x_directory = std::string(filepath).substr(0, std::string(filepath).find_last_of('/'));
	this->x_processNode(scene->mRootNode, scene);

	for (unsigned int i = 0; i < meshes.size(); i++) {
		meshes[i]->setUpMesh();
	}

}

void ModelImporter::x_processNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		//TODO:mesh wrapper need to develop
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.emplace_back(this->x_processMesh(mesh, scene));

	}
	//going recursively to every children
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		this->x_processNode(node->mChildren[i], scene);
	}
}

Mesh* ModelImporter::x_processMesh(aiMesh* mesh, const aiScene* scene)
{

	//TODO:trail for efficiency
	Mesh* modelMesh = new Mesh();

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertexData;
		glm::vec3 placeholder;

		placeholder.x = mesh->mVertices[i].x;
		placeholder.y = mesh->mVertices[i].y;
		placeholder.z = mesh->mVertices[i].z;
		vertexData.Position = placeholder;

		if (mesh->HasNormals()) {
			placeholder.x = mesh->mNormals[i].x;
			placeholder.y = mesh->mNormals[i].y;
			placeholder.z = mesh->mNormals[i].z;
			vertexData.Normal = placeholder;
		}
		if (mesh->mTextureCoords[0]) {
			glm::vec2 coords;

			coords.x = mesh->mTextureCoords[0][i].x;
			coords.y = mesh->mTextureCoords[0][i].y;

			vertexData.TexCoords = coords;

			//placeholder.x = mesh->mTangents[i].x;
			//placeholder.y = mesh->mTangents[i].y;
			//placeholder.z = mesh->mTangents[i].z;
			//vertexData.Tangent = placeholder;

			//placeholder.x = mesh->mBitangents[i].x;
			//placeholder.y = mesh->mBitangents[i].y;
			//placeholder.z = mesh->mBitangents[i].z;
			//vertexData.Bitangent = placeholder;
		}
		else vertexData.TexCoords = glm::vec2(0.f,0.f);
		

		modelMesh->vertices.emplace_back(vertexData);
	}
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) 
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++) 
		{
			modelMesh->indices.emplace_back(face.mIndices[j]);
		}
	}

	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	
	std::vector<Texture> diffuseMaps = x_loadMaterialTextures(material, aiTextureType::aiTextureType_DIFFUSE, "texture_diffuse");
	modelMesh->textures.insert(modelMesh->textures.end(),diffuseMaps.begin(),diffuseMaps.end());
	
	std::vector<Texture> specularMaps = x_loadMaterialTextures(material, aiTextureType::aiTextureType_SPECULAR, "texture_specular");
	modelMesh->textures.insert(modelMesh->textures.end(),specularMaps.begin(),specularMaps.end());

	std::vector<Texture> normalMaps = x_loadMaterialTextures(material, aiTextureType::aiTextureType_HEIGHT, "texture_normal");
	modelMesh->textures.insert(modelMesh->textures.end(), normalMaps.begin(), normalMaps.end());

	std::vector<Texture> heightMaps = x_loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
	modelMesh->textures.insert(modelMesh->textures.end(), heightMaps.begin(), heightMaps.end());

	return modelMesh;
}

std::vector<Texture> ModelImporter::x_loadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < material->GetTextureCount(type); i++) 
	{
		aiString str;
		material->GetTexture(type, i, &str);
		bool skip = false;
		for (unsigned int j = 0; j < textures_loaded.size(); j++) 
		{
			if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
			{
				textures.emplace_back(textures_loaded[j]);
				skip = true;
				break;
			}
		}
		if (!skip) 
		{
			Texture texture;
			//texture.id = this->x_textureFromFile(str.C_Str(), this->x_directory,0);
			std::string filepath = std::string(str.C_Str());
			filepath = this->x_directory + '/' + filepath;
			texture.id = TextureFactory::createTextureUnit(filepath.c_str());
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.emplace_back(texture);
		}

	}
	return textures;
}