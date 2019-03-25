#include "Model.h"


Model::Model(std::string path)
{
	loadModel(path);
}

Model::~Model()
{
}

void Model::Draw(Shader * shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw(shader);
	}
}

void Model::loadModel(std::string path)
{
	Assimp::Importer importer;
	//ReadFile(·�����������ν��д���|UV��ת|�������߿ռ�);
	const aiScene* scene = importer.ReadFile(path,aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)//�������Ϊ��||����δ���||����û�нڵ�
	{
		std::cout << "Assimp error" << std::endl;
		return;
	}

	directory = path.substr(0,path.find_last_of("\\"));
	//std::cout << "Success!" << directory << std::endl;

	processNode(scene->mRootNode,scene);
}

void Model::processNode(aiNode * node,const aiScene * scene)
{
	//std::cout << node->mName.data << std::endl;

	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* curMesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(curMesh,scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i],scene);
	}
}

Mesh Model::processMesh(aiMesh * mesh, const aiScene * scene)
{
	//����
	std::vector<Vertex> tempVertices;
	std::vector<unsigned int> tempIndices;
	std::vector<Texture> tempTextures;

	glm::vec3 tempVec;
	//����
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex tempVertex;
		//��λ��
		tempVertex.Position.x = mesh->mVertices[i].x;
		tempVertex.Position.y = mesh->mVertices[i].y;
		tempVertex.Position.z = mesh->mVertices[i].z;
		//�ڷ���
		tempVertex.Normal.x = mesh->mNormals[i].x;
		tempVertex.Normal.y = mesh->mNormals[i].y;
		tempVertex.Normal.z = mesh->mNormals[i].z;

		if (mesh->mTextureCoords[0])
		{
			tempVertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
			tempVertex.TexCoords.y = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			tempVertex.TexCoords = glm::vec2(0,0);
		}

		tempVertices.push_back(tempVertex);
	}
	//����
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)//���������
	{
		for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; j++)//����ÿ���������
		{
			tempIndices.push_back(mesh->mFaces[i].mIndices[j]);
		}
	}

	//����
	if (mesh->mMaterialIndex >=0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		//������
		//std::vector<Texture> diffuseMaps = loadMaterialTextures(material,aiTextureType_DIFFUSE,"texture_diffuse");
		//�߹ⷴ��
	}

	return Mesh(tempVertices, tempIndices, {});
}

//std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName) {
//	
//	std::vector<Texture> textures;
//
//	//�������ʵ���������(һ������)
//	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
//	{
//		aiString str;
//		//��ͼ��λ�ø�str
//		mat->GetTexture(type,i,&str);
//		//
//
//	}
//}