#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <fstream>
#include <iostream>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <vector>
#include <stdio.h>
#include <string>
#include "Model3D.h"

class Model3DLoader
{

public:
	Model3D* loadData(const std::string path);
	Model3D* loadData(const std::string path3D, const std::string pathTexture);
};

/*
Returns the VAO ID
*/
Model3D* Model3DLoader::loadData(const std::string path) {
	Assimp::Importer importer;
	const aiScene* theScene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs);

	if (!theScene)
	{
		std::cout << "ERROR ASSIMP " << __FILE__ << __LINE__ << std::endl;
		return NULL;
	}

	Model3D nuevoModelo;

	aiMesh* mesh = theScene->mMeshes[0];//Empiezo cargando 1 solo mesh por file.
	//aiVector3D* vertices = mesh->mVertices;
	aiVector3D* normals = mesh->mNormals;
	aiVector3D** texCoords = mesh->mTextureCoords;
	

	std::vector<unsigned int> indices;
	std::vector<aiVector3D> vertices;
	std::vector< aiVector3D > textureCoordinates; //solo usa xy

	for (int i = 0; i < mesh->mNumVertices; i++) {
		textureCoordinates.push_back(mesh->mTextureCoords[0][i]);
	}

	for (int i = 0; i < mesh->mNumVertices; i++) {
		vertices.push_back(mesh->mVertices[i]);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	aiMaterial* material = theScene->mMaterials[mesh->mMaterialIndex];


	glm::vec3 vertice;
	vertice.x = vertices[11].x;
	vertice.y = vertices[11].y;
	vertice.z = vertices[11].z;
	std::cout << "Nombre del archivo es: " << vertice.y << std::endl;

	glm::vec2 textCoord;
	textCoord.x = texCoords[0][0].x;
	textCoord.y = texCoords[0][0].y;


	return NULL;
}

Model3D* Model3DLoader::loadData(const std::string path3D, const std::string pathTexture) {

}
