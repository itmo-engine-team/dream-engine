#pragma once

#include <vector>

#include "../Shader/Vertex.h"

class MeshData
{
public:

    MeshData(std::vector<Vertex> vertices, std::vector<DWORD> indices);

    const std::vector<Vertex>& GetVertices() const;
    const std::vector<DWORD>& GetIndices() const;
    UINT GetIndicesCount() const;

protected:

    std::vector<Vertex> vertices;
    std::vector<DWORD> indices;
    UINT indicesCount;

};

