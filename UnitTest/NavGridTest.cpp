#include "pch.h"

#include "NavMesh.h"

TEST(NavGridTest, initGrid)
{
    NavMesh* testNav = new NavMesh(Vector3(5, 5, 5), Vector3(4, 4, 4), 1);
}