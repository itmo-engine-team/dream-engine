#pragma once

#include <vector>

#include "MeshData.h"

class MeshRenderer;

class ModelData
{
public:

    ModelData();
    ModelData(MeshRenderer* pMeshRenderer, const std::string& filePath, Texture* texture);

    void AddMeshData(MeshData* pMeshData);
    std::vector<MeshData*> GetMeshDataList() const;
    
    Texture* GetTexture() const;

protected:

    std::vector<MeshData*> meshesData;

    Texture* texture = nullptr;

};

