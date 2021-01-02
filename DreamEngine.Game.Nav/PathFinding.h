#pragma once

#include <vector>

#include "NavMesh.h"
//
//struct PolygonCost
//{
//    NavMeshPolygon OwnerPolygon;
//    NavMeshPolygon ParentPolygonCost;
//    float GCost = 0;
//    float HCost = 0;
//    float GetFCost() { return GCost + HCost; }
//};

class PathFinding
{

public:

    std::vector<NavMeshPolygon> FindPath(NavMesh* navMesh, Vector3 centerStartNode, Vector3 centerTargetNode);

private:

    float euclidean(Vector3 start, Vector3 end);
    std::vector<NavMeshPolygon> retracePath(NavMeshPolygon startNode, NavMeshPolygon targetNode);

};

