#pragma once

#include "assimp/scene.h"
#include "assimp/mesh.h"
#include "assimp/Importer.hpp"

#include "ModelData.h"
#include "ModelShader.h"

using namespace Assimp;

class MeshRenderer
{
public:

    MeshRenderer();

    bool ProcessModel(ModelData* modelData, const std::string& filePath);

    static ModelData* CreateBoxModel(ModelShader* shader, Vector4 color, Vector3 boxSize);
    static ModelData* CreateSquareModel(ModelShader* shader, Vector3 quardSize);

protected:

    void processNode(ModelData* modelData, aiNode* node, const aiScene* scene);
    static MeshData* processMesh(aiMesh* mesh, const aiScene* scene);

};

