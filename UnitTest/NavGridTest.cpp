#include "pch.h"

#include "NavMesh.h"

TEST(NavGridTest, initGrid)
{
    NavMesh* testNav = new NavMesh(Vector3(5, 5, 5), Vector3(4, 4, 4), 1);

    std::cout << testNav->GetGrid()[0][0].VertexRD->Pos.x << "x\n";
    std::cout << testNav->GetGrid()[0][0].VertexRD->Pos.y << "y\n";
    std::cout << testNav->GetGrid()[0][0].VertexRD->Pos.z << "z\n";
}