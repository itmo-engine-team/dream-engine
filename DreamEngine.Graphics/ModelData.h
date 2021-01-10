#pragma once

#include <vector>

#include "MeshData.h"

class MeshRenderer;

class ModelData
{
public:

    ModelData() = default;
    ModelData(MeshRenderer* pMeshRenderer, const std::string& filePath);
    ~ModelData();

    bool IsValid() const;
    float GetLowestVertexY() const;

    void AddMeshData(MeshData* meshData);
    std::vector<MeshData*> GetMeshDataList() const;

protected:

    bool isValid = true;
    float lowestVertexY = 1000;

    std::vector<MeshData*> meshesData;

};

