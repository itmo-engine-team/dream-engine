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
    int polygonIndex = -1;
    for (auto column : navMeshGrid)
    {
        for (NavMeshPolygon* polygon : column)
        {
            polygonIndex++;
            float leftEdge = worldPosition.z - collisionSize.x;
            float rightEdge = worldPosition.z + collisionSize.x;
            float topEdge = worldPosition.x + collisionSize.y;
            float downEdge = worldPosition.x - collisionSize.y;

            if(leftEdge > polygon->Center.z || polygon->Center.z > rightEdge) continue;
            if(downEdge > polygon->Center.x || polygon->Center.x  > topEdge) continue;

            polygon->IsFree = false;

            meshData->GetVertices().at(polygonIndex).Color = Vector4{ 1, 0, 0, 0 };
            meshData->GetVertices().at(polygonIndex + 1).Color = Vector4{ 1, 0, 0, 0 };
            meshData->GetVertices().at(polygonIndex + 2).Color = Vector4{ 1, 0, 0, 0 };
            meshData->GetVertices().at(polygonIndex + 3).Color = Vector4{ 1, 0, 0, 0 };
        }
    }
}

void NavMesh::initNavMeshGrid()
{
    // Calculate Center of coordinates of zero polygon
    Vector3 centerFirstPolygon;
    centerFirstPolygon.x = position.x + size.y / 2 - polygonSize / 2; //TODO: debugCheck
    centerFirstPolygon.y = position.y;
    centerFirstPolygon.z = position.z - size.x / 2 + polygonSize / 2; //TODO: debugCheck

    std::vector<Vertex> vertices;
    
    DWORD currentVertexIndex = 0;
    for (int x = 0; x < size.x; x++)
    {
        std::vector <NavMeshPolygon*> navMeshRow;
        for (int z = 0; z < size.y; z++)
        {
            NavMeshPolygon* polygon = new NavMeshPolygon;      
            polygon->Center.x = centerFirstPolygon.x - polygonSize * x; //TODO: debugCheck
            polygon->Center.y = centerFirstPolygon.y;
            polygon->Center.z = polygonSize * z + centerFirstPolygon.z; //TODO: debugCheck
            initVertex(*polygon);

            polygon->FirstVertexIndex = currentVertexIndex;

            vertices.push_back(*polygon->VertexLD);
            vertices.push_back(*polygon->VertexLT);
            vertices.push_back(*polygon->VertexRT);
            vertices.push_back(*polygon->VertexRD);

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

void NavMesh::initVertex(NavMeshPolygon& polygon) const
{
    float halfPolygonSize = polygonSize / 2;

    polygon.VertexLT = new Vertex
    {
        Vector3{ polygon.Center.x + halfPolygonSize, polygon.Center.y, polygon.Center.z - halfPolygonSize },
        Vector4{ 0, 1, 0, 1 },
        Vector3::Up
    };
    polygon.VertexLD = new Vertex
    {
        Vector3{ polygon.Center.x - halfPolygonSize, polygon.Center.y, polygon.Center.z - halfPolygonSize },
        Vector4{ 0, 1, 0, 1 },
        Vector3::Up
    };
    polygon.VertexRT = new Vertex
    {
        Vector3{ polygon.Center.x + halfPolygonSize, polygon.Center.y, polygon.Center.z + halfPolygonSize },
        Vector4{ 0, 1, 0, 1 },
        Vector3::Up
    };
    polygon.VertexRD = new Vertex
    {
        Vector3{ polygon.Center.x - halfPolygonSize, polygon.Center.y, polygon.Center.z + halfPolygonSize },
        Vector4{ 0, 1, 0, 1 },
        Vector3::Up
    };
}
