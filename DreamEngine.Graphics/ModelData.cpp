#include "ModelData.h"

#include "MeshRenderer.h"

ModelData::ModelData(MeshRenderer* pMeshRenderer, const std::string& filePath, Texture* texture)
    : texture(texture)
{
    isValid = pMeshRenderer->ProcessModel(this, filePath);
}

bool ModelData::IsValid() const
{
    return isValid;
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
