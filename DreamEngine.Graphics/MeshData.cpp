#include "MeshData.h"

MeshData::MeshData(std::vector<Vertex> vertices, std::vector<DWORD> indices, bool isTriangleTopology)
    : isTriangleTopology(isTriangleTopology), vertices(vertices), indices(indices)
{
    indicesCount = std::size(indices);

    for (const Vertex& vertex : vertices)
    {
        if (vertex.Pos.y < lowestVertexY)
            lowestVertexY = vertex.Pos.y;
    }
}

bool MeshData::IsTriangleTopology() const
{
    return isTriangleTopology;
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

float MeshData::GetLowestVertexY() const
{
    return lowestVertexY;
}
