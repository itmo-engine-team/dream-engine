#pragma once

#include <vector>

#include "MeshData.h"
#include "ModelShader.h"

class MeshRenderer;

class ModelData
{
public:

    ModelData(ModelShader* shader);
    ModelData(MeshRenderer* pMeshRenderer, const std::string& filePath, ModelShader* shader, Texture* texture);

    void AddMeshData(MeshData* pMeshData);
    std::vector<MeshData*> GetMeshDataList() const;

    ModelShader* GetShader() const;
    Texture* GetTexture() const;

protected:

    std::vector<MeshData*> meshesData;

    ModelShader* shader;
    Texture* texture = nullptr;

};

