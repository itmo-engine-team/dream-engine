#include "MeshData.h"

MeshData::MeshData(std::vector<Vertex> vertices, std::vector<DWORD> indices, Texture* texture)
    : vertices(vertices), indices(indices), texture(texture)
{
    indicesCount = std::size(indices);

    for (const Vertex& vertex : vertices)
    {
        if (vertex.Pos.y < lowestVertexY)
            lowestVertexY = vertex.Pos.y;
    }
}

std::vector<Vertex>& MeshData::GetVertices()
{
    return vertices;
}

const std::vector<DWORD>& MeshData::GetIndices() const
{
    return indices;
}

UINT MeshData::GetIndicesCount() const
{
    return indicesCount;
}

Texture* MeshData::GetTexture() const
{
    return texture;
}

float MeshData::GetLowestVertexY() const
{
    return lowestVertexY;
}
