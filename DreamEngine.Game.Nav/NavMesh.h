#pragma once

#include "SimpleMath.h"
#include "Vertex.h"

class MeshData;

using namespace DirectX::SimpleMath;

struct NavMeshPolygon
{
    Vector3 center;
    Vertex* VertexLT;
    Vertex* VertexLD;
    Vertex* VertexRT;
    Vertex* VertexRD;
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

    std::vector<std::vector<NavMeshPolygon>> GetGrid() const;

protected:

    Vector2 size;
    Vector3 position;
    float polygonSize;
    MeshData* meshData;

    std::vector<std::vector<NavMeshPolygon>> navMeshGrid;

    void initNavMeshGrid();
    void initVertex(NavMeshPolygon& polygon) const;
};

