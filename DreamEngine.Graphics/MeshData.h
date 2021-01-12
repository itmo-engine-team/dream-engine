#pragma once

#include <vector>

#include "Vertex.h"

class Texture;

class MeshData
{
public:

    MeshData(std::vector<Vertex> vertices, std::vector<DWORD> indices, bool isTriangleTopology = true);

    bool IsTriangleTopology() const;
    void SetTriangleTopology(bool isTriangleTopology);
    std::vector<Vertex>& GetVertices();
    const std::vector<DWORD>& GetIndices() const;
    UINT GetIndicesCount() const;

    float GetLowestVertexY() const;

protected:

    bool isTriangleTopology;
    std::vector<Vertex> vertices;
    std::vector<DWORD> indices;
    UINT indicesCount;

    float lowestVertexY = 1000;

};

