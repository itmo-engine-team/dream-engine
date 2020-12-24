#pragma once

#include "SimpleMath.h"
#include "../DreamEngine.Graphics/Vertex.h"

using namespace DirectX::SimpleMath;

struct NavMeshPolygon
{
    Vector3 centerCoordinate;
    Vertex* VerteLT;
    Vertex* VerteLD;
    Vertex* VerteRT;
    Vertex* VerteRD;
};

class NavMesh
{

public:
    NavMesh() = delete;
    NavMesh(Vector3 navMeshPosition, Vector3 navMeshSize, float polySize);

    Vector2 GetSize() const;

    float GetPolygonSize() const;
    void SetPolygonSize(float polySize);

    Vector3 GetPosition() const;

    std::vector<std::vector<NavMeshPolygon>> GetGrid() const;

protected:

    Vector2 size;
    Vector3 position;
    float polygonSize;

    std::vector<std::vector<NavMeshPolygon>> navMeshGrid;

    void initNavMeshGrid();
    void initVertex(NavMeshPolygon& polygon) const;
};

