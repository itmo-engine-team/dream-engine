#pragma once

#include <vector>

#include "MeshData.h"
#include "TexturedShader.h"

class MeshRenderer;

class ModelData
{
public:

    ModelData(TexturedShader* shader);
    ModelData(MeshRenderer* pMeshRenderer, const std::string& filePath, TexturedShader* shader);

    void AddMeshData(MeshData* pMeshData);
    std::vector<MeshData*> GetMeshDataList() const;

    TexturedShader* GetShader() const;

protected:

    std::vector<MeshData*> meshesData;

    TexturedShader* shader;

};

