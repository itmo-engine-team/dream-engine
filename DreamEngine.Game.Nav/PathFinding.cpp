#include "PathFinding.h"

std::vector<NavMeshPolygon*> PathFinding::FindPath(void* actor, NavMesh* navMesh, Vector3 locationStartPolygon, NavMeshPolygon* targetPolygon, bool canMoveByDiagonal)
{
    std::vector <PolygonCost*> openPolygonsCost;
    std::vector <PolygonCost*> closedPolygonsCost;

    PolygonCost* startPolygonCost = new PolygonCost { navMesh->FindPolygon(locationStartPolygon) };
    PolygonCost* targetPolygonCost = new PolygonCost { targetPolygon };

    openPolygonsCost.push_back(startPolygonCost);

    while (!openPolygonsCost.empty())
    {
        PolygonCost* currentPolygonCost = openPolygonsCost.at(0);
        for (int i = 1; i < openPolygonsCost.size(); i++)
        {
            if (openPolygonsCost.at(i)->GetFCost() < currentPolygonCost->GetFCost() ||
                openPolygonsCost.at(i)->GetFCost() == currentPolygonCost->GetFCost() && openPolygonsCost.at(i)->HCost < currentPolygonCost->HCost)
            {
                currentPolygonCost = openPolygonsCost.at(i);
            }
        }

        openPolygonsCost.erase(std::find(openPolygonsCost.begin(), openPolygonsCost.end(), currentPolygonCost));
        closedPolygonsCost.push_back(currentPolygonCost);

        if (currentPolygonCost->OwnerPolygon->FirstVertexIndex == targetPolygonCost->OwnerPolygon->FirstVertexIndex)
            return retracePath(startPolygonCost, currentPolygonCost);

        for (NavMeshPolygon* neighbour : navMesh->GetNeighbours(currentPolygonCost->OwnerPolygon, canMoveByDiagonal))
        {
            PolygonCost* neighbourCost = findPolygonInArray(closedPolygonsCost, neighbour);

            if (!neighbour->IsFreeForActor(actor) || neighbourCost != nullptr)
                continue;
          
            float newCostToNeighbour = currentPolygonCost->GCost + euclidian(currentPolygonCost->OwnerPolygon->Center, neighbour->Center);
            neighbourCost = findPolygonInArray(openPolygonsCost, neighbour);
            if (neighbourCost == nullptr)
                neighbourCost = new PolygonCost{ neighbour };

            if (newCostToNeighbour < neighbourCost->GCost || neighbourCost->GCost < 0)
            {
                neighbourCost->GCost = newCostToNeighbour;
                neighbourCost->HCost = euclidian(neighbour->Center, targetPolygonCost->OwnerPolygon->Center);
                neighbourCost->ParentPolygonCost = currentPolygonCost;
                if (std::find(openPolygonsCost.begin(), openPolygonsCost.end(), neighbourCost) == openPolygonsCost.end())
                    openPolygonsCost.push_back(neighbourCost);
            }
        }
    }
    return {};
}

std::vector<NavMeshPolygon*> PathFinding::retracePath(PolygonCost* startPolygon, PolygonCost* targetPolygon)
{
    std::vector<NavMeshPolygon*> path;
    PolygonCost* currentPolygon = targetPolygon;

    while (currentPolygon != startPolygon)
    {
        path.push_back(currentPolygon->OwnerPolygon);
        currentPolygon = currentPolygon->ParentPolygonCost;
    }

    std::reverse(path.begin(), path.end());
    return path;
}

PolygonCost* PathFinding::findPolygonInArray(std::vector<PolygonCost*> polygonCost, NavMeshPolygon* polygon)
{
    for (PolygonCost* i : polygonCost)
    {
        if (i->OwnerPolygon->FirstVertexIndex == polygon->FirstVertexIndex)
            return i;
    }
    return nullptr;
}

float PathFinding::euclidian(Vector3 start, Vector3 end)
{
    Vector3 delta = end - start;
    return sqrt(pow(delta.x, 2) + pow(delta.y, 2));
}
