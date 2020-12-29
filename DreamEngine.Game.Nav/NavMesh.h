#pragma once

#include "SimpleMath.h"
#include "Vertex.h"

class MeshData;

using namespace DirectX::SimpleMath;

struct NavMeshPolygon
{
    int FirstVertexIndex;
    Vector3 Center;
    Vertex* VertexLT;
    Vertex* VertexLD;
    Vertex* VertexRT;
    Vertex* VertexRD;
    bool IsFree = true;
};

class NavMesh
{

public:

    NavMesh() = delete;
    NavMesh(Vector3 navMeshPosition, Vector3 planeSize, float polySize);

    Vector2 GetSize() const;

    float GetPolygonSize() const;
    void SetPolygonSize(float polySize);

    Vector3 GetPosition() const;

    MeshData* GetMeshData() const;

    std::vector<std::vector<NavMeshPolygon*>> GetGrid() const;

    void UpdatePolygons(Vector3 worldPosition, Vector2 collisionSize);

protected:

    Vector2 size;
    Vector3 position;
    float polygonSize;
    MeshData* meshData;
    std::vector<DWORD> indices;

    std::vector<std::vector<NavMeshPolygon*>> navMeshGrid;

    void initNavMeshGrid();
    void initVertex(NavMeshPolygon& polygon) const;  
};