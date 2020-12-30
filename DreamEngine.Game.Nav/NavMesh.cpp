#include "NavMesh.h"

#include "MeshData.h"

NavMesh::NavMesh(Vector3 navMeshPosition, Vector3 planeSize, float polySize)
{
    size = Vector2(planeSize.x, planeSize.z);
    if (planeSize.x > planeSize.z)
        size.y = planeSize.x;
    else
        size.x = planeSize.z;

    polygonSize = polySize;
    position = navMeshPosition;

    initNavMeshGrid();
}

Vector2 NavMesh::GetSize() const
{
    return size;
}

float NavMesh::GetPolygonSize() const
{
    return polygonSize;
}

void NavMesh::SetPolygonSize(float polySize)
{
    polygonSize = polySize;
}

Vector3 NavMesh::GetPosition() const
{
    return position;
}

MeshData* NavMesh::GetMeshData() const
{
    return meshData;
}

std::vector<std::vector<NavMeshPolygon*>> NavMesh::GetGrid() const
{
    return navMeshGrid;
}


void NavMesh::UpdatePolygons(Vector3 worldPosition, Vector2 collisionSize)
{
    for (auto column : navMeshGrid)
    {
        for (NavMeshPolygon* polygon : column)
        {
            float leftEdge = worldPosition.z - collisionSize.x;
            float rightEdge = worldPosition.z + collisionSize.x;
            float topEdge = worldPosition.x + collisionSize.y;
            float downEdge = worldPosition.x - collisionSize.y;

            if(leftEdge > polygon->Center.z || polygon->Center.z > rightEdge) continue;
            if(downEdge > polygon->Center.x || polygon->Center.x  > topEdge) continue;

            polygon->IsFree = false;

            meshData->GetVertices().at(polygon->FirstVertexIndex).Color = RED;
            meshData->GetVertices().at(polygon->FirstVertexIndex + 1).Color = RED;
            meshData->GetVertices().at(polygon->FirstVertexIndex + 2).Color = RED;
            meshData->GetVertices().at(polygon->FirstVertexIndex + 3).Color = RED;
        }
    }
}

void NavMesh::initNavMeshGrid()
{
    // Calculate Center of coordinates of zero polygon
    Vector3 centerFirstPolygon;
    centerFirstPolygon.x = position.x + size.y / 2 - polygonSize / 2;
    centerFirstPolygon.y = position.y;
    centerFirstPolygon.z = position.z - size.x / 2 + polygonSize / 2;

    std::vector<Vertex> vertices;
    
    DWORD currentVertexIndex = 0;
    for (int x = 0; x < size.x; x++)
    {
        std::vector <NavMeshPolygon*> navMeshRow;
        for (int z = 0; z < size.y; z++)
        {
            NavMeshPolygon* polygon = new NavMeshPolygon;      
            polygon->Center.x = centerFirstPolygon.x - polygonSize * x;
            polygon->Center.y = centerFirstPolygon.y;
            polygon->Center.z = polygonSize * z + centerFirstPolygon.z;

            std::vector<Vertex> polygonVertices;
            polygonVertices = initVertex(*polygon);
            vertices.insert(vertices.end(), polygonVertices.begin(), polygonVertices.end());

            polygon->FirstVertexIndex = currentVertexIndex;

            std::vector<DWORD> polygonIndices = {
                0 + currentVertexIndex, 1 + currentVertexIndex, 2 + currentVertexIndex,
                0 + currentVertexIndex, 2 + currentVertexIndex, 3 + currentVertexIndex,
            };
            indices.insert(indices.end(), polygonIndices.begin(), polygonIndices.end());

            navMeshRow.push_back(polygon);

            currentVertexIndex += 4;
        }
        navMeshGrid.push_back(navMeshRow);
    }
    meshData = new MeshData(vertices, indices);
}

std::vector<Vertex> NavMesh::initVertex(NavMeshPolygon& polygon) 
{
    std::vector<Vertex> vertices;
    float halfPolygonSize = polygonSize / 2;

    Vertex vertexLD = Vertex
    {
        Vector3{ polygon.Center.x - halfPolygonSize, polygon.Center.y, polygon.Center.z - halfPolygonSize },
        Vector4{ 0, 1, 0, 1 },
        Vector3::Up
    };
    vertices.push_back(vertexLD);

    Vertex vertexLT = Vertex
    {
        Vector3{ polygon.Center.x + halfPolygonSize, polygon.Center.y, polygon.Center.z - halfPolygonSize },
        Vector4{ 0, 1, 0, 1 },
        Vector3::Up
    };
    vertices.push_back(vertexLT);

    Vertex vertexRT = Vertex
    {
        Vector3{ polygon.Center.x + halfPolygonSize, polygon.Center.y, polygon.Center.z + halfPolygonSize },
        Vector4{ 0, 1, 0, 1 },
        Vector3::Up
    };
    vertices.push_back(vertexRT);

    Vertex vertexRD = Vertex
    {
        Vector3{ polygon.Center.x - halfPolygonSize, polygon.Center.y, polygon.Center.z + halfPolygonSize },
        Vector4{ 0, 1, 0, 1 },
        Vector3::Up
    };
    vertices.push_back(vertexRD);
    return vertices;
}

void NavMesh::ResetPolygons()
{
    for (auto column : navMeshGrid)
    {
        for (NavMeshPolygon* polygon : column)
        {
            polygon->IsFree = true;

            meshData->GetVertices().at(polygon->FirstVertexIndex).Color = GREEN;
            meshData->GetVertices().at(polygon->FirstVertexIndex + 1).Color = GREEN;
            meshData->GetVertices().at(polygon->FirstVertexIndex + 2).Color = GREEN;
            meshData->GetVertices().at(polygon->FirstVertexIndex + 3).Color = GREEN;
        }
    }
}
