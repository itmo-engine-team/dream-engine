#pragma once

#include "SimpleMath.h"
#include "Vertex.h"

class MeshData;
class ModelData;

using namespace DirectX::SimpleMath;

struct NavMeshPolygon
{
    int FirstVertexIndex;
    Vector3 Center;
    std::vector<void*> Actors;

    Vector3 LD;
    Vector3 LT;
    Vector3 RT;
    Vector3 RD;

    bool IsFreeForActor(void* actor);

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
    ModelData* GetModelData() const;
    std::vector<std::vector<NavMeshPolygon*>> GetGrid() const;
    std::vector<NavMeshPolygon*> GetNeighbours(NavMeshPolygon* polygon, bool canMoveByDiagonal);

    void UpdatePolygons(void* actor, Vector3 worldPosition, Vector2 collisionSize);
    void ResetPolygons();
    NavMeshPolygon* FindPolygon(Vector3 location);

    void DebugPath(std::vector<NavMeshPolygon*> path);

protected:

    Vector2 size;
    Vector3 position;
    float polygonSize;
    MeshData* meshData;
    ModelData* modelData;
    std::vector<DWORD> indices;

    std::vector<std::vector<NavMeshPolygon*>> navMeshGrid;

    void initNavMeshGrid();
    std::vector<Vertex> initVertex(NavMeshPolygon& polygon);
    bool checkPolygonCollision(Vector3 collisionPosition, Vector2 collisionSize, NavMeshPolygon* polygon);
};