#include "ACF_Movement.h"
#include "SimpleMath.h"
#include "DeltaTimeHandler.h"
#include "Transform.h"

ACF_Movement::ACF_Movement(ActorContext* context, Actor* actor) : ActorComponentFixed(context, actor)
{
    pathFindingInst = new PathFinding();
}

bool ACF_Movement::MoveTo(Vector3 targetLocation)
{
    if (!pathIsValid())
        path = pathFindingInst->FindPath(actor, context->GetNavMesh(), actor->GetTransform()->GetWorldPosition(), targetLocation, moveByDiagonal);

    if (path.empty()) return false;

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
    if (toTarget.Length() < actorSpeed * context->GetDeltaTimeHandler()->GetDeltaTime())
    {
        actor->GetTransform()->SetWorldPosition(path.at(0)->Center);
        path.erase(path.begin());
    }
    else
    {
        toTarget.Normalize();
        actor->GetTransform()->AddWorldPosition(toTarget * actorSpeed * context->GetDeltaTimeHandler()->GetDeltaTime());
    }
}

