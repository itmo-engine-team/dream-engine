#include "PathFinding.h"

std::vector<NavMeshPolygon> PathFinding::FindPath(NavMesh* navMesh, Vector3 centerStartNode, Vector3 centerTargetNode)
{
    std::vector <NavMeshPolygon*> openPolygons;
    std::vector <NavMeshPolygon*> closedPolygons;

    //PolygonCost* startNode = new PolygonCost { *navMesh->FindPolygon(centerStartNode) };
    //PolygonCost* targetNode = new PolygonCost { *navMesh->FindPolygon(centerTargetNode) };
    
    NavMeshPolygon startNode = *navMesh->FindPolygon(centerStartNode);
    NavMeshPolygon targetNode = *navMesh->FindPolygon(centerTargetNode);
    openPolygons.push_back(&startNode);

    while (!openPolygons.empty())
    {
        NavMeshPolygon* currentNode = openPolygons.at(0);
        for (int i = 1; i < openPolygons.size(); i++)
        {
            if (openPolygons.at(i)->GetFCost() < currentNode->GetFCost() ||
                openPolygons.at(i)->GetFCost() == currentNode->GetFCost() && openPolygons.at(i)->HCost < currentNode->HCost)
            {
                currentNode = openPolygons.at(i);
            }
        }

        openPolygons.erase(std::find(openPolygons.begin(), openPolygons.end(), currentNode));
        closedPolygons.push_back(currentNode);

        if (currentNode->Center == targetNode.Center)
            return retracePath(startNode, *currentNode);

        for (NavMeshPolygon* neighbour : navMesh->GetNeighbours(currentNode))
        {
            if (!neighbour->IsFree || std::find(closedPolygons.begin(), closedPolygons.end(), neighbour) != closedPolygons.end())
                continue;

            float newCostToNeighbour = currentNode->GCost + euclidean(currentNode->Center, neighbour->Center);
            if (newCostToNeighbour < neighbour->GCost || std::find(openPolygons.begin(), openPolygons.end(), neighbour) == openPolygons.end())
            {
                neighbour->GCost = newCostToNeighbour;
                neighbour->HCost = euclidean(neighbour->Center, targetNode.Center);
                neighbour->ParentPolygon = currentNode;
                if (std::find(openPolygons.begin(), openPolygons.end(), neighbour) == openPolygons.end())
                    openPolygons.push_back(neighbour);
            }
        }
    }
}

float PathFinding::euclidean(Vector3 start, Vector3 end)
{
    Vector3 delta = end - start;
    return sqrt(pow(delta.x, 2) + pow(delta.z, 2));
}

std::vector<NavMeshPolygon> PathFinding::retracePath(NavMeshPolygon startNode, NavMeshPolygon targetNode)
{
    std::vector<NavMeshPolygon> path;
    NavMeshPolygon* currentPolygon = &targetNode;

    while (currentPolygon->Center != startNode.Center)
    {
        path.push_back(*currentPolygon);
        currentPolygon = currentPolygon->ParentPolygon;
    }

    std::reverse(path.begin(), path.end());
    return path;
}
