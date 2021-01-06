#pragma once

#include <vector>

#include "NavMesh.h"

struct PolygonCost
{
    NavMeshPolygon* OwnerPolygon;
    PolygonCost* ParentPolygonCost;
    float GCost = -1;
    float HCost = -1;
    float GetFCost() { return GCost + HCost; }
};

class PathFinding
{

public:

    std::vector<NavMeshPolygon*> FindPath(void* actor, NavMesh* navMesh, Vector3 locationStartPolygon, Vector3 locationTargetPolygon, bool canMoveByDiagonal);

private:

    float euclidean(Vector3 start, Vector3 end);
    std::vector<NavMeshPolygon*> retracePath(PolygonCost* startPolygon, PolygonCost* targetPolygon);
    PolygonCost* findPolygonInArray(std::vector <PolygonCost*> polygonCost, NavMeshPolygon* polygon);

};

