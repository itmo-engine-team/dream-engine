#include "ACF_Movement.h"
#include "SimpleMath.h"
#include "DeltaTimeHandler.h"
#include "Transform.h"

ACF_Movement::ACF_Movement(Actor* actor) : ActorComponentFixed(actor)
{
    pathFindingInst = new PathFinding();
}

bool ACF_Movement::MoveTo(Vector3 targetLocation)
{
    if (polygonCount == 2 || path.empty())
    {
        NavMeshPolygon* targetPolygon = findFreeClosestPolygon(targetLocation);
        path = pathFindingInst->FindPath(actor, actor->GetContext()->GetNavMesh(), actor->GetTransform()->GetWorldPosition(), targetPolygon, moveByDiagonal);
        polygonCount = 0;
    }

    if (path.empty()) return false;

    actor->GetContext()->GetNavMesh()->DebugPath(path);
    changeLocation();
    return true;
}

float ACF_Movement::GetSpeed()
{
    return actorSpeed;
}

void ACF_Movement::SetSpeed(float newSpeed)
{
    actorSpeed = newSpeed;
}

bool ACF_Movement::GetCanMoveByDiagonal()
{
    return moveByDiagonal;
}

void ACF_Movement::SetCanMoveByDiagonal(bool canMoveByDiagonal)
{
    moveByDiagonal = canMoveByDiagonal;
}

bool ACF_Movement::pathIsValid()
{
    if (path.empty()) return false;

    for (NavMeshPolygon* polygon : path)
    {
        if (!polygon->IsFreeForActor(actor))
            return false;
    }

    return true;
}

void ACF_Movement::changeLocation()
{
    Vector3 toTarget = path.at(0)->Center - actor->GetTransform()->GetWorldPosition();
    if (toTarget.Length() < actorSpeed * actor->GetContext()->GetDeltaTimeHandler()->GetDeltaTime())
    {
        actor->GetTransform()->SetWorldPosition(path.at(0)->Center);
        path.erase(path.begin());
        polygonCount++;
    }
    else
    {
        toTarget.Normalize();
        actor->GetTransform()->AddWorldPosition(toTarget * actorSpeed * actor->GetContext()->GetDeltaTimeHandler()->GetDeltaTime());
    }
}

NavMeshPolygon* ACF_Movement::findFreeClosestPolygon(Vector3 targetLocation)
{
    NavMeshPolygon* targetPolygon = actor->GetContext()->GetNavMesh()->FindPolygon(targetLocation);

    if (targetPolygon->IsFreeForActor(actor))
        return targetPolygon;

    std::vector<NavMeshPolygon*> uncheckPolygons;
    std::vector<NavMeshPolygon*> checkedPolygons;
    uncheckPolygons.push_back(targetPolygon);
    void* targetRef = targetPolygon->Actors.at(0);
    targetPolygon = nullptr;

    while (!uncheckPolygons.empty())
    {
        NavMeshPolygon* currentPolygon = uncheckPolygons.at(0);
        checkedPolygons.push_back(uncheckPolygons.at(0));
        uncheckPolygons.erase(uncheckPolygons.begin());

        NavMesh* navMesh = actor->GetContext()->GetNavMesh();
        for (NavMeshPolygon* neighbour : navMesh->GetNeighbours(currentPolygon, moveByDiagonal))
        {
            if (neighbour->IsFreeForActor(actor) && (targetPolygon == nullptr || 
                Vector3::Distance(neighbour->Center, actor->GetTransform()->GetWorldPosition()) < Vector3::Distance(targetPolygon->Center, actor->GetTransform()->GetWorldPosition())))
            {
                targetPolygon = neighbour;
                continue;
            }

            if (std::find(neighbour->Actors.begin(), neighbour->Actors.end(), targetRef) != neighbour->Actors.end() && 
                std::find(checkedPolygons.begin(), checkedPolygons.end(), neighbour) == checkedPolygons.end())
                uncheckPolygons.push_back(neighbour);
        }
    }

    return targetPolygon;
}

