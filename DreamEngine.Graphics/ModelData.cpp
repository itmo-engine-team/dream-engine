#include "ModelData.h"

#include "MeshRenderer.h"

ModelData::ModelData(ModelShader* shader)
    : shader(shader)
{

}

ModelData::ModelData(MeshRenderer* pMeshRenderer, const std::string& filePath, ModelShader* shader, Texture* texture)
    : shader(shader), texture(texture)
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

ModelShader* ModelData::GetShader() const
{
    return shader;
}

Texture* ModelData::GetTexture() const
{
    return texture;
}
