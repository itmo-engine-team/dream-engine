#pragma once

#include <d3d11_1.h>

#include "assimp/scene.h"
#include "assimp/mesh.h"
#include "assimp/Importer.hpp"

#include <vector>
#include "Vertex.h"

class Game;
class ModelObject;
class MeshObject;
class Shader;

using namespace Assimp;

class MeshRenderer
{
public:
	MeshRenderer(Game* game);
	
	bool addModel(ModelObject* model, const std::string& filePath, Shader* shader);
	void processNode(ModelObject* model, aiNode* node, const aiScene* scene, Shader* shader);
	MeshObject* processMesh(aiMesh* mesh, const aiScene* scene, Shader* shader);

private:
	Game* m_game;
};

