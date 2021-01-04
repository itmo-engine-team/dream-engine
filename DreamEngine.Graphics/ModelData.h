#pragma once

#include <vector>

#include "MeshData.h"

class MeshRenderer;

class ModelData
{
public:

    ModelData() = default;
    ModelData(MeshRenderer* pMeshRenderer, const std::string& filePath, Texture* texture);

    bool IsValid() const;
    float GetLowestVertexY() const;

    void AddMeshData(MeshData* meshData);
    std::vector<MeshData*> GetMeshDataList() const;
    
    Texture* GetTexture() const;

protected:

    bool isValid = true;
    float lowestVertexY = 1000;

    std::vector<MeshData*> meshesData;

    Texture* texture = nullptr;

};

