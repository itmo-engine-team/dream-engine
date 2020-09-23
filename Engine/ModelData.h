#pragma once

#include <vector>
#include "MeshData.h"
#include "Shader.h"

class MeshRenderer;

class ModelData
{
public:

    ModelData(Shader* shader);
    ModelData(MeshRenderer* pMeshRenderer, const std::string& filePath, Shader* shader);

    void AddMeshData(MeshData* pMeshData);
    std::vector<MeshData*> GetMeshDataList() const;

    Shader* GetShader() const;

protected:

    std::vector<MeshData*> meshesData;

    Shader* shader;

};

