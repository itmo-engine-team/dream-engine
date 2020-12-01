#pragma once

#include "assimp/scene.h"
#include "assimp/mesh.h"
#include "assimp/Importer.hpp"

#include "ModelData.h"

using namespace Assimp;

class MeshRenderer
{
public:

    MeshRenderer() = default;

    bool ProcessModel(ModelData* modelData, const std::string& filePath);

    static ModelData* CreateBoxModel(Vector4 color, Vector3 boxSize);
    static ModelData* CreateSquareModel(Vector3 quardSize);

protected:

    void processNode(ModelData* modelData, aiNode* node, const aiScene* scene);
    static MeshData* processMesh(aiMesh* mesh, const aiScene* scene, Texture* texture);

};

