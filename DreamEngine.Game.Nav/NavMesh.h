#pragma once

#include "SimpleMath.h"
#include "Vertex.h"

class MeshData;

using namespace DirectX::SimpleMath;

struct NavMeshPolygon
{
    int FirstVertexIndex;
    Vector3 Center;
    bool IsFree = true;

    NavMeshPolygon* ParentPolygon;
    float GCost = 0;
    float HCost = 0;
    float GetFCost() { return GCost + HCost; }

private:

    friend class NavMesh;
    int x;
    int z;
};

class NavMesh
{

public:

    NavMesh() = delete;
    NavMesh(Vector3 navMeshPosition, Vector3 planeSize, float polySize);

    const Vector4 OCCUPIED_POLYGON_COLOR = { 1, 0, 0, 1 };
    const Vector4 FREE_POLYGON_COLOR = { 0, 1, 0, 1 };
    const Vector4 PATH_COLOR = { 0, 0, 1, 1 };

    Vector2 GetSize() const;

    float GetPolygonSize() const;
    void SetPolygonSize(float polySize);

    Vector3 GetPosition() const;
    MeshData* GetMeshData() const;
    std::vector<std::vector<NavMeshPolygon*>> GetGrid() const;
    std::vector<NavMeshPolygon*> GetNeighbours(NavMeshPolygon* polygon);

    void UpdatePolygons(Vector3 worldPosition, Vector2 collisionSize);
    void ResetPolygons();
    NavMeshPolygon* FindPolygon(Vector3 centerLocation);

    void DebugPath(std::vector<NavMeshPolygon> path);

protected:

    Vector2 size;
    Vector3 position;
    float polygonSize;
    MeshData* meshData;
    std::vector<DWORD> indices;

    std::vector<std::vector<NavMeshPolygon*>> navMeshGrid;

    void initNavMeshGrid();
    std::vector<Vertex> initVertex(NavMeshPolygon& polygon);
    bool checkPolygonCollision(NavMeshPolygon* polygon, Vector2 actorCollisionEdge);
};