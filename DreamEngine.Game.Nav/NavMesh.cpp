#include "NavMesh.h"

#include <iostream>

NavMesh::NavMesh(Vector3 navMeshPosition, Vector3 navMeshSize, float polySize)
{
    size = Vector2(navMeshSize.x, navMeshSize.z);
    if (navMeshSize.x > navMeshSize.z)
        size.y = navMeshSize.x;
    else
        size.x = navMeshSize.z;

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
    Vector3 centreFirstPolygon;
    centreFirstPolygon.x = position.x + size.y / 2 - polygonSize/2; //TODO: debugCheck
    centreFirstPolygon.y = position.y;
    centreFirstPolygon.z = position.z - size.x / 2 + polygonSize / 2; //TODO: debugCheck

    for (int x = 0; x < size.x; x++)
    {
        for (int y = 0; y < size.y; y++ )
        {
            std::vector <NavMeshPolygon> navMeshRow;

            NavMeshPolygon polygon;      
            polygon.centerCoordinate.x = polygonSize * y + centreFirstPolygon.x; //TODO: debugCheck
            polygon.centerCoordinate.y = centreFirstPolygon.y;
            polygon.centerCoordinate.z = polygonSize * x + centreFirstPolygon.z; //TODO: debugCheck

            initVertex(polygon);
            navMeshRow.push_back(polygon);

            navMeshGrid.push_back(navMeshRow);
        }
    }
}

void NavMesh::initVertex(NavMeshPolygon& polygon) const
{
    float halfPolygonSize = polygonSize / 2;

    polygon.VerteLT = new Vertex
    {
        Vector3{ polygon.centerCoordinate.x + halfPolygonSize, polygon.centerCoordinate.y, polygon.centerCoordinate.z - halfPolygonSize },
        Vector4{ 0, 1, 0, 1 },
        Vector3::Up
    };
    polygon.VerteLD = new Vertex
    {
        Vector3{ polygon.centerCoordinate.x - halfPolygonSize, polygon.centerCoordinate.y, polygon.centerCoordinate.z - halfPolygonSize },
        Vector4{ 0, 1, 0, 1 },
        Vector3::Up
    };
    polygon.VerteRT = new Vertex
    {
        Vector3{ polygon.centerCoordinate.x + halfPolygonSize, polygon.centerCoordinate.y, polygon.centerCoordinate.z + halfPolygonSize },
        Vector4{ 0, 1, 0, 1 },
        Vector3::Up
    };
    polygon.VerteRD = new Vertex
    {
        Vector3{ polygon.centerCoordinate.x - halfPolygonSize, polygon.centerCoordinate.y, polygon.centerCoordinate.z + halfPolygonSize },
        Vector4{ 0, 1, 0, 1 },
        Vector3::Up
    };
}
