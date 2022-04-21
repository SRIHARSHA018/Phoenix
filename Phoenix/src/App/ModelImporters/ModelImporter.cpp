#include "ModelImporter.h"


ModelImporter::ModelImporter(const char* file_path, unsigned int shader_program_id)
	:x_shader_program_id(shader_program_id)
{
	position = glm::vec3(0.f);
	rotation = glm::vec3(0.f);
	scale = glm::vec3(1.f);
	this->x_loadModel(file_path);

}

ModelImporter::~ModelImporter()
{
	for (unsigned int i = 0; i < meshes.size(); i++) {
		delete meshes[i];
	}
}

void ModelImporter::update()
{
	this->x_updateUniforms();
	this->x_draw();
}

void ModelImporter::onEvent(IEvent& event)
{
}

void ModelImporter::x_loadModel(const char* file_path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(file_path,
		aiProcess_FlipUVs |
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_RemoveRedundantMaterials |
		aiProcess_OptimizeGraph |
		aiProcess_OptimizeMeshes |
		aiProcess_SplitLargeMeshes |
		aiProcess_JoinIdenticalVertices |
		aiProcess_ImproveCacheLocality);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}

	this->x_directory = std::string(file_path).substr(0, std::string(file_path).find_last_of('/'));
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

void ModelImporter::x_updateUniforms()
{
	UniformManager::get()->setUniformMatrix4fv("model", this->x_shader_program_id, glm::value_ptr(this->x_getModelMatrix()));

}

void ModelImporter::x_draw()
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->draw(this->x_shader_program_id);
	}
}

glm::mat4 ModelImporter::x_getModelMatrix()
{
	glm::mat4 model_matrix = glm::mat4(1.f);
	model_matrix = glm::scale(model_matrix, scale);
	model_matrix = glm::rotate(model_matrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
	model_matrix = glm::rotate(model_matrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
	model_matrix = glm::rotate(model_matrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
	model_matrix = glm::translate(model_matrix, position);
	return model_matrix;
}

Mesh* ModelImporter::x_processMesh(aiMesh* mesh, const aiScene* scene)
{

	//TODO:trail for efficiency
	Mesh* model_mesh = new Mesh();

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex_data;
		glm::vec3 placeholder;

		placeholder.x = mesh->mVertices[i].x;
		placeholder.y = mesh->mVertices[i].y;
		placeholder.z = mesh->mVertices[i].z;
		vertex_data.position = placeholder;

		if (mesh->HasNormals()) {
			placeholder.x = mesh->mNormals[i].x;
			placeholder.y = mesh->mNormals[i].y;
			placeholder.z = mesh->mNormals[i].z;
			vertex_data.normal = placeholder;
		}
		if (mesh->mTextureCoords[0]) {
			glm::vec2 coords;

			coords.x = mesh->mTextureCoords[0][i].x;
			coords.y = mesh->mTextureCoords[0][i].y;

			vertex_data.tex_coords = coords;

			//placeholder.x = mesh->mTangents[i].x;
			//placeholder.y = mesh->mTangents[i].y;
			//placeholder.z = mesh->mTangents[i].z;
			//vertexData.Tangent = placeholder;

			//placeholder.x = mesh->mBitangents[i].x;
			//placeholder.y = mesh->mBitangents[i].y;
			//placeholder.z = mesh->mBitangents[i].z;
			//vertexData.Bitangent = placeholder;
		}
		else vertex_data.tex_coords = glm::vec2(0.f, 0.f);


		model_mesh->vertices.emplace_back(vertex_data);
	}
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			model_mesh->indices.emplace_back(face.mIndices[j]);
		}
	}

	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

	std::vector<Texture> diffuse_maps = x_loadMaterialTextures(material, aiTextureType::aiTextureType_DIFFUSE, "texture_diffuse");
	model_mesh->textures.insert(model_mesh->textures.end(), diffuse_maps.begin(), diffuse_maps.end());

	std::vector<Texture> specular_maps = x_loadMaterialTextures(material, aiTextureType::aiTextureType_SPECULAR, "texture_specular");
	model_mesh->textures.insert(model_mesh->textures.end(), specular_maps.begin(), specular_maps.end());

	std::vector<Texture> normal_maps = x_loadMaterialTextures(material, aiTextureType::aiTextureType_HEIGHT, "texture_normal");
	model_mesh->textures.insert(model_mesh->textures.end(), normal_maps.begin(), normal_maps.end());

	std::vector<Texture> height_maps = x_loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
	model_mesh->textures.insert(model_mesh->textures.end(), height_maps.begin(), height_maps.end());

	return model_mesh;
}

std::vector<Texture> ModelImporter::x_loadMaterialTextures(aiMaterial* material, aiTextureType type, std::string type_name)
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
			std::string file_path = std::string(str.C_Str());
			file_path = this->x_directory + '/' + file_path;
			texture.id = TextureFactory::createTextureUnit(file_path.c_str());
			texture.type = type_name;
			texture.path = str.C_Str();
			textures.emplace_back(texture);
		}

	}
	return textures;
}