#include "NavMesh.h"

#include <iostream>

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

std::vector<std::vector<NavMeshPolygon>> NavMesh::GetGrid() const
{
    return navMeshGrid;
}

void NavMesh::initNavMeshGrid()
{
    // Calculate center of coordinates of zero polygon
    Vector3 centerFirstPolygon;
    centerFirstPolygon.x = position.x + size.y / 2 - polygonSize / 2; //TODO: debugCheck
    centerFirstPolygon.y = position.y;
    centerFirstPolygon.z = position.z - size.x / 2 + polygonSize / 2; //TODO: debugCheck

    for (int x = 0; x < size.x; x++)
    {
        std::vector <NavMeshPolygon> navMeshRow;
        for (int y = 0; y < size.y; y++)
        {
            NavMeshPolygon polygon;      
            polygon.center.x = polygonSize * y + centerFirstPolygon.x; //TODO: debugCheck
            polygon.center.y = centerFirstPolygon.y;
            polygon.center.z = polygonSize * x + centerFirstPolygon.z; //TODO: debugCheck

            initVertex(polygon);
            navMeshRow.push_back(polygon);
        }
        navMeshGrid.push_back(navMeshRow);
    }
}

void NavMesh::initVertex(NavMeshPolygon& polygon) const
{
    float halfPolygonSize = polygonSize / 2;

    polygon.VertexLT = new Vertex
    {
        Vector3{ polygon.center.x + halfPolygonSize, polygon.center.y, polygon.center.z - halfPolygonSize },
        Vector4{ 0, 1, 0, 1 },
        Vector3::Up
    };
    polygon.VertexLD = new Vertex
    {
        Vector3{ polygon.center.x - halfPolygonSize, polygon.center.y, polygon.center.z - halfPolygonSize },
        Vector4{ 0, 1, 0, 1 },
        Vector3::Up
    };
    polygon.VertexRT = new Vertex
    {
        Vector3{ polygon.center.x + halfPolygonSize, polygon.center.y, polygon.center.z + halfPolygonSize },
        Vector4{ 0, 1, 0, 1 },
        Vector3::Up
    };
    polygon.VertexRD = new Vertex
    {
        Vector3{ polygon.center.x - halfPolygonSize, polygon.center.y, polygon.center.z + halfPolygonSize },
        Vector4{ 0, 1, 0, 1 },
        Vector3::Up
    };
}
