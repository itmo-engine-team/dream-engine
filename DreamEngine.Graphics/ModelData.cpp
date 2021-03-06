#include "ModelData.h"

#include "MeshRenderer.h"

ModelData::ModelData(MeshRenderer* pMeshRenderer, const std::string& filePath)
{
    isValid = pMeshRenderer->ProcessModel(this, filePath);
}

ModelData::~ModelData()
{
    for (auto meshData : meshesData)
    {
        delete meshData;
    }
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

float ModelData::GetLowestVertexY() const
{
    return lowestVertexY;
}
