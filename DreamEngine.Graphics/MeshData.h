#pragma once

#include <vector>

#include "Vertex.h"

class Texture;

class MeshData
{
public:

    MeshData(std::vector<Vertex> vertices, std::vector<DWORD> indices, Texture* texture = nullptr);

    std::vector<Vertex>& GetVertices();
    const std::vector<DWORD>& GetIndices() const;
    UINT GetIndicesCount() const;

    Texture* GetTexture() const;

protected:

    std::vector<Vertex> vertices;
    std::vector<DWORD> indices;
    UINT indicesCount;

    Texture* texture;

};

