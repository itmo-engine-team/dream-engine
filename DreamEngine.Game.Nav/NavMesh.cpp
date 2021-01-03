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

std::vector<NavMeshPolygon*> NavMesh::GetNeighbours(NavMeshPolygon* polygon, bool canMoveByDiagonal)
{
    std::vector<NavMeshPolygon*> neighbours;

    for (int x = -1; x <= 1; x++)
    {
        for (int z = -1; z <= 1; z++)
        {
            if (x == 0 && z == 0) continue;
            if (!canMoveByDiagonal && (x == -1 && z == -1 || x == -1 && z == 0 || 
                x == 1 && z == -1 || x == 1 && z == 1)) continue;

            int checkX = polygon->x + x;
            int checkZ = polygon->z + z;

            if (checkX >= 0 && checkX < navMeshGrid.size() && checkZ >= 0 && checkZ < navMeshGrid.size())
                neighbours.push_back(GetGrid().at(checkX).at(checkZ));
        }
    }
    return neighbours;
}

void NavMesh::UpdatePolygons(Vector3 worldPosition, Vector2 collisionSize)
{
    for (auto column : navMeshGrid)
    {
        for (NavMeshPolygon* polygon : column)
        {
            /*Vector2 leftCollisionEdge = Vector2{ worldPosition.z - collisionSize.x, worldPosition.x };
            Vector2 rightCollisionEdge = Vector2{ worldPosition.z + collisionSize.x, worldPosition.x };
            Vector2 topCollisionEdge = Vector2{ worldPosition.z, worldPosition.x + collisionSize.y };
            Vector2 downCollisionEdge = Vector2{ worldPosition.z, worldPosition.x - collisionSize.y };*/

            if (checkPolygonCollision(worldPosition, collisionSize, polygon->Center))
            {
                polygon->IsFree = false;

                meshData->GetVertices().at(polygon->FirstVertexIndex).Color = OCCUPIED_POLYGON_COLOR;
                meshData->GetVertices().at(polygon->FirstVertexIndex + 1).Color = OCCUPIED_POLYGON_COLOR;
                meshData->GetVertices().at(polygon->FirstVertexIndex + 2).Color = OCCUPIED_POLYGON_COLOR;
                meshData->GetVertices().at(polygon->FirstVertexIndex + 3).Color = OCCUPIED_POLYGON_COLOR;
            }
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
    float x = 0;
    int countX = 0;
    while ( x < size.x)
    {
        std::vector <NavMeshPolygon*> navMeshRow;
        float z = 0;
        int countZ = 0;
        while (z < size.y)
        {
            NavMeshPolygon* polygon = new NavMeshPolygon;
            polygon->Center.x = centerFirstPolygon.x - polygonSize * countX;
            polygon->Center.y = centerFirstPolygon.y;
            polygon->Center.z = polygonSize * countZ + centerFirstPolygon.z;

            polygon->x = countX;
            polygon->z = countZ;

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
            z += polygonSize;
            countZ++;
        }
        navMeshGrid.push_back(navMeshRow);
        countX++;
        x += polygonSize;
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

bool NavMesh::checkPolygonCollision(Vector3 collisionPosition, Vector2 collisionSize, Vector3 polygonLocation)
{
    Vector2 leftCollisionEdge = Vector2{ collisionPosition.z - collisionSize.x, collisionPosition.x };
    Vector2 rightCollisionEdge = Vector2{ collisionPosition.z + collisionSize.x, collisionPosition.x };
    Vector2 topCollisionEdge = Vector2{ collisionPosition.z, collisionPosition.x + collisionSize.y };
    Vector2 downCollisionEdge = Vector2{ collisionPosition.z, collisionPosition.x - collisionSize.y };

    if (downCollisionEdge.y <= polygonLocation.x && topCollisionEdge.y >= polygonLocation.x)
    {
        if (leftCollisionEdge.x <= polygonLocation.z && rightCollisionEdge.x >= polygonLocation.z)
            return true;
    }
        
    return false;
}

void NavMesh::ResetPolygons()
{
    for (auto column : navMeshGrid)
    {
        for (NavMeshPolygon* polygon : column)
        {
            polygon->IsFree = true;

            meshData->GetVertices().at(polygon->FirstVertexIndex).Color = FREE_POLYGON_COLOR;
            meshData->GetVertices().at(polygon->FirstVertexIndex + 1).Color = FREE_POLYGON_COLOR;
            meshData->GetVertices().at(polygon->FirstVertexIndex + 2).Color = FREE_POLYGON_COLOR;
            meshData->GetVertices().at(polygon->FirstVertexIndex + 3).Color = FREE_POLYGON_COLOR;
        }
    }
}

NavMeshPolygon* NavMesh::FindPolygon(Vector3 location)
{
    NavMeshPolygon* findedPolygon = new NavMeshPolygon{};
    float distance = -1;
    for (auto xRow : navMeshGrid)
    {
        for (NavMeshPolygon* polygon : xRow)
        {
            float newDistance = Vector3::Distance(polygon->Center, location);
            if (newDistance <= distance || distance < 0)
            {
                findedPolygon = polygon;
                distance = newDistance;
            }
        }
    }
    return findedPolygon;
}

void NavMesh::DebugPath(std::vector<NavMeshPolygon*> path)
{
    for (NavMeshPolygon* polygon : path)
    {
        meshData->GetVertices().at(polygon->FirstVertexIndex).Color = PATH_COLOR;
        meshData->GetVertices().at(polygon->FirstVertexIndex + 1).Color = PATH_COLOR;
        meshData->GetVertices().at(polygon->FirstVertexIndex + 2).Color = PATH_COLOR;
        meshData->GetVertices().at(polygon->FirstVertexIndex + 3).Color = PATH_COLOR;
    }
}
