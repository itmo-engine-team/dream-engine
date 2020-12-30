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
};

class NavMesh
{

public:

    NavMesh() = delete;
    NavMesh(Vector3 navMeshPosition, Vector3 planeSize, float polySize);

    const Vector4 RED = { 1, 0, 0, 0 };
    const Vector4 GREEN = { 0, 1, 0, 0 };

    Vector2 GetSize() const;

    float GetPolygonSize() const;
    void SetPolygonSize(float polySize);

    Vector3 GetPosition() const;

    MeshData* GetMeshData() const;

    std::vector<std::vector<NavMeshPolygon*>> GetGrid() const;

    void UpdatePolygons(Vector3 worldPosition, Vector2 collisionSize);
    void ResetPolygons();

protected:

    Vector2 size;
    Vector3 position;
    float polygonSize;
    MeshData* meshData;
    std::vector<DWORD> indices;

    std::vector<std::vector<NavMeshPolygon*>> navMeshGrid;

    void initNavMeshGrid();
    std::vector<Vertex> initVertex(NavMeshPolygon& polygon);
};