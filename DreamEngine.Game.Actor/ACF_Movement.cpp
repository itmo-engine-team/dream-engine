#include "ACF_Movement.h"
#include "SimpleMath.h"
#include "DeltaTimeHandler.h"
#include "Transform.h"
#include "ParamFloat.h"

ACF_Movement::ACF_Movement(Actor* actor) : ActorComponentFixed(actor)
{
    pathFindingInst = new PathFinding();

    actorSpeed = new ParamFloat();
    AddParam("Actor Speed", actorSpeed);
}

bool ACF_Movement::MoveTo(Vector3 targetLocation)
{
    if (polygonCount == 2 || path.empty())
    {
        NavMeshPolygon* targetPolygon = actor->GetContext()->GetNavMesh()->FindFreeClosestPolygon(targetLocation, actor, actor->GetTransform()->GetWorldPosition(), moveByDiagonal);
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
    return actorSpeed->Get();
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
    if (toTarget.Length() < actorSpeed->Get() * actor->GetContext()->GetDeltaTimeHandler()->GetDeltaTime())
    {
        actor->GetTransform()->SetWorldPosition(path.at(0)->Center);
        path.erase(path.begin());
        polygonCount++;
    }
    else
    {
        toTarget.Normalize();
        actor->GetTransform()->AddWorldPosition(toTarget * actorSpeed->Get() * actor->GetContext()->GetDeltaTimeHandler()->GetDeltaTime());
    }
}
