#pragma once

#include "Vertex.h"

class MeshData
{
public:

    MeshData(std::vector<Vertex> vertices,
        std::vector<DWORD> indices);

    std::vector<Vertex> GetVertices() const;
    std::vector<DWORD> GetIndices() const;
    UINT GetIndicesCount() const;

protected:

    std::vector<Vertex> vertices;
    std::vector<DWORD> indices;
    UINT indicesCount;
    
};

