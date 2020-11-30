#include "ModelData.h"

#include "MeshRenderer.h"

ModelData::ModelData()
{

}

ModelData::ModelData(MeshRenderer* pMeshRenderer, const std::string& filePath, Texture* texture)
    : texture(texture)
{
    pMeshRenderer->ProcessModel(this, filePath);
}

void ModelData::AddMeshData(MeshData* pMeshData)
{
    meshesData.push_back(pMeshData);
}

std::vector<MeshData*> ModelData::GetMeshDataList() const
{
    return meshesData;
}

Texture* ModelData::GetTexture() const
{
    return texture;
}
