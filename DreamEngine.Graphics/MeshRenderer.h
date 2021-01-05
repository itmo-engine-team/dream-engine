#pragma once

#include "ModelData.h"

struct aiMesh;
struct aiScene;
struct aiNode;

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
