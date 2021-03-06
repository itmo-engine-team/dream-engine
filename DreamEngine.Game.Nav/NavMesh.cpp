#include "NavMesh.h"

#include <algorithm>

#include "MeshData.h"
#include "ModelData.h"

bool NavMeshPolygon::IsFreeForActor(void* actor)
{
    if (this->Actors.size() > 1)
        return false;

    if (!this->Actors.empty() && std::find(this->Actors.begin(), this->Actors.end(), actor) == this->Actors.end())
        return false;

    return true;
}

NavMesh::NavMesh(Vector3 navMeshPosition, Vector3 planeSize, float polySize)
{
    size = Vector2(planeSize.x, planeSize.z);
    if (planeSize.x > planeSize.z)
        size.y = planeSize.x;
    else
        size.x = planeSize.z;

    polygonSize = polySize;
    position = navMeshPosition;

    meshData = nullptr;

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

ModelData* NavMesh::GetModelData() const
{
    return modelData;
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
            if (!canMoveByDiagonal && x != 0 && z != 0) continue;

            int checkX = polygon->x + x;
            int checkZ = polygon->z + z;

            if (checkX >= 0 && checkX < navMeshGrid.size() && checkZ >= 0 && checkZ < navMeshGrid.size())
                neighbours.push_back(GetGrid().at(checkZ).at(checkX));
        }
    }
    return neighbours;
}

void NavMesh::UpdatePolygons(void* actor, Vector3 worldPosition, Vector2 collisionSize)
{
    for (auto column : navMeshGrid)
    {
        for (NavMeshPolygon* polygon : column)
        {
            if (checkPolygonCollision(worldPosition, collisionSize, polygon))
            {
                polygon->Actors.push_back(actor);

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
    centerFirstPolygon.x = position.x - size.x / 2 + polygonSize / 2;
    centerFirstPolygon.y = position.y;
    centerFirstPolygon.z = position.z + size.y / 2 - polygonSize / 2;

    std::vector<Vertex> vertices;
    std::vector<Vertex> gridVertices;
    
    DWORD currentVertexIndex = 0;
    float z = 0;
    int countZ = 0;
    while (z < size.y)
    {
        std::vector <NavMeshPolygon*> navMeshRow;
        float x = 0;
        int countX = 0;
        while (x < size.x)
        {
            NavMeshPolygon* polygon = new NavMeshPolygon;
            polygon->Center.x = centerFirstPolygon.x + polygonSize * countX;
            polygon->Center.y = centerFirstPolygon.y;
            polygon->Center.z = polygonSize * countZ - centerFirstPolygon.z;

            polygon->x = countX;
            polygon->z = countZ;

            std::vector<Vertex> polygonVertices;
            polygonVertices = initVertex(*polygon, Vector4{ 0, 1, 0, 1 });
            vertices.insert(vertices.end(), polygonVertices.begin(), polygonVertices.end());

            std::vector<Vertex> polygonGridVertices;
            polygonGridVertices = initVertex(*polygon, Vector4{ 0, 0.2f, 1, 1 });
            gridVertices.insert(gridVertices.end(), polygonGridVertices.begin(), polygonGridVertices.end());

            polygon->FirstVertexIndex = currentVertexIndex;

            std::vector<DWORD> polygonIndices = {
                0 + currentVertexIndex, 1 + currentVertexIndex, 2 + currentVertexIndex,
                0 + currentVertexIndex, 2 + currentVertexIndex, 3 + currentVertexIndex,
            };
            indices.insert(indices.end(), polygonIndices.begin(), polygonIndices.end());

            std::vector<DWORD> polygonGridIndices = {
                0 + currentVertexIndex, 1 + currentVertexIndex,
                1 + currentVertexIndex, 2 + currentVertexIndex,
                2 + currentVertexIndex, 3 + currentVertexIndex,
                3 + currentVertexIndex, 0 + currentVertexIndex,
            };
            gridIndices.insert(gridIndices.end(), polygonGridIndices.begin(), polygonGridIndices.end());

            navMeshRow.push_back(polygon);

            currentVertexIndex += 4;
            x += polygonSize;
            countX++;
        }
        navMeshGrid.push_back(navMeshRow);
        countZ++;
        z += polygonSize;
    }

    meshData = new MeshData(vertices, indices);
    gridMeshData = new MeshData(gridVertices, gridIndices, false);
    modelData = new ModelData();
    modelData->AddMeshData(meshData);
    modelData->AddMeshData(gridMeshData);
}

std::vector<Vertex> NavMesh::initVertex(NavMeshPolygon& polygon, Vector4 color)
{
    std::vector<Vertex> vertices;
    float halfPolygonSize = polygonSize / 2;

    polygon.LD = Vector3{ polygon.Center.x - halfPolygonSize, polygon.Center.y, polygon.Center.z - halfPolygonSize };
    Vertex vertexLD = Vertex
    {
        polygon.LD,
        color,
        Vector3::Up
    };
    vertices.push_back(vertexLD);

    polygon.LT = Vector3{ polygon.Center.x - halfPolygonSize, polygon.Center.y, polygon.Center.z + halfPolygonSize };
    Vertex vertexLT = Vertex
    {
        polygon.LT,
        color,
        Vector3::Up
    };
    vertices.push_back(vertexLT);

    polygon.RT = Vector3{ polygon.Center.x + halfPolygonSize, polygon.Center.y, polygon.Center.z + halfPolygonSize };
    Vertex vertexRT = Vertex
    {
        polygon.RT,
        color,
        Vector3::Up
    };
    vertices.push_back(vertexRT);

    polygon.RD = Vector3{ polygon.Center.x + halfPolygonSize, polygon.Center.y, polygon.Center.z - halfPolygonSize };
    Vertex vertexRD = Vertex
    {
        polygon.RD,
        color,
        Vector3::Up
    };
    vertices.push_back(vertexRD);
    return vertices;
}

bool NavMesh::checkPolygonCollision(Vector3 collisionPosition, Vector2 collisionSize, NavMeshPolygon* polygon)
{
    float leftCollisionEdge = collisionPosition.x - collisionSize.x;
    float rightCollisionEdge = collisionPosition.x + collisionSize.x;
    float topCollisionEdge = collisionPosition.z + collisionSize.y;
    float downCollisionEdge = collisionPosition.z - collisionSize.y;

    if (max(leftCollisionEdge, polygon->LT.x) <= min(rightCollisionEdge, polygon->RT.x) &&
        max(downCollisionEdge, polygon->LD.z) <= min(topCollisionEdge, polygon->LT.z))
    {
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
            polygon->Actors.clear();

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
    if (!isDebug) return;

    for (NavMeshPolygon* polygon : path)
    {
        meshData->GetVertices().at(polygon->FirstVertexIndex).Color = PATH_COLOR;
        meshData->GetVertices().at(polygon->FirstVertexIndex + 1).Color = PATH_COLOR;
        meshData->GetVertices().at(polygon->FirstVertexIndex + 2).Color = PATH_COLOR;
        meshData->GetVertices().at(polygon->FirstVertexIndex + 3).Color = PATH_COLOR;
    }
}

bool NavMesh::IsDebug()
{
    return isDebug;
}

void NavMesh::SetIsDebug(bool isDebug)
{
    this->isDebug = isDebug;
}

NavMeshPolygon* NavMesh::FindFreeClosestPolygon(Vector3 targetLocation, void* ownerActor, Vector3 ownerWorldPosition, bool canMoveByDiagonal)
{
    NavMeshPolygon* targetPolygon = FindPolygon(targetLocation);

    if (targetPolygon->IsFreeForActor(ownerActor))
        return targetPolygon;

    std::vector<NavMeshPolygon*> uncheckPolygons;
    std::vector<NavMeshPolygon*> checkedPolygons;
    uncheckPolygons.push_back(targetPolygon);
    void* targetRef = targetPolygon->Actors.at(0);
    targetPolygon = nullptr;

    while (!uncheckPolygons.empty())
    {
        NavMeshPolygon* currentPolygon = uncheckPolygons.at(0);
        checkedPolygons.push_back(uncheckPolygons.at(0));
        uncheckPolygons.erase(uncheckPolygons.begin());

     
        for (NavMeshPolygon* neighbour : GetNeighbours(currentPolygon, canMoveByDiagonal))
        {
            if (neighbour->IsFreeForActor(ownerActor) && (targetPolygon == nullptr ||
                Vector3::Distance(neighbour->Center, ownerWorldPosition) < Vector3::Distance(targetPolygon->Center, ownerWorldPosition)))
            {
                targetPolygon = neighbour;
                continue;
            }

            if (std::find(neighbour->Actors.begin(), neighbour->Actors.end(), targetRef) != neighbour->Actors.end() &&
                std::find(checkedPolygons.begin(), checkedPolygons.end(), neighbour) == checkedPolygons.end())
                uncheckPolygons.push_back(neighbour);
        }
    }
    return targetPolygon;
}
