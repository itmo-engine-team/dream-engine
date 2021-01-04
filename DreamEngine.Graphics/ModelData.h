#pragma once

#include <vector>

#include "MeshData.h"

class MeshRenderer;

class ModelData
{
public:

    ModelData() = default;
    ModelData(MeshRenderer* pMeshRenderer, const std::string& filePath, Texture* texture);

    void AddMeshData(MeshData* meshData);
    std::vector<MeshData*> GetMeshDataList() const;
    
    Texture* GetTexture() const;

    float GetLowestVertexY() const;

protected:

    std::vector<MeshData*> meshesData;

    Texture* texture = nullptr;

    float lowestVertexY = 1000;

};

