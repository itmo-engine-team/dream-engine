#include "ModelData.h"

#include "MeshRenderer.h"

ModelData::ModelData(MeshRenderer* pMeshRenderer, const std::string& filePath, Texture* texture)
    : texture(texture)
{
    pMeshRenderer->ProcessModel(this, filePath);
}

void ModelData::AddMeshData(MeshData* meshData)
{
    meshesData.push_back(meshData);

    if (meshData->GetLowestVertexY() < lowestVertexY)
        lowestVertexY = meshData->GetLowestVertexY();
}

std::vector<MeshData*> ModelData::GetMeshDataList() const
{
    return meshesData;
}

Texture* ModelData::GetTexture() const
{
    return texture;
}

float ModelData::GetLowestVertexY() const
{
    return lowestVertexY;
}
