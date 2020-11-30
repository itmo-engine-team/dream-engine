#include "MeshData.h"

MeshData::MeshData(std::vector<Vertex> vertices, std::vector<DWORD> indices, Texture* texture)
    : vertices(vertices), indices(indices), texture(texture)
{
    indicesCount = std::size(indices);
}

const std::vector<Vertex>& MeshData::GetVertices() const
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
