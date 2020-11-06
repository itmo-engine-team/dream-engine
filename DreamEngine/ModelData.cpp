#include "ModelData.h"

#include "MeshRenderer.h"

ModelData::ModelData(TexturedShader* shader)
    : shader(shader)
{

}

ModelData::ModelData(MeshRenderer* pMeshRenderer, const std::string& filePath, TexturedShader* shader)
    : shader(shader)
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

TexturedShader* ModelData::GetShader() const
{
    return shader;
}
