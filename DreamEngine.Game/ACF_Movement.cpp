#include "ACF_Movement.h"
#include "SimpleMath.h"

ACF_Movement::ACF_Movement(ActorContext* context, Actor* actor) : ActorComponentFixed(context, actor)
{
    pathFindingInst = new PathFinding();
}

void ACF_Movement::MoveTo(NavMesh* navMesh, Vector3 locationStartPolygon, Vector3 locationTargetPolygon, bool canMoveByDiagonal)
{
    if (!pathIsValid())
        path = pathFindingInst->FindPath(actor, navMesh, locationStartPolygon, locationTargetPolygon, canMoveByDiagonal);

    if (path.empty()) return;

    changeLocation();
}

float ACF_Movement::GetSpeed()
{
    return actorSpeed;
}

void ACF_Movement::SetSpeed(float newSpeed)
{
    actorSpeed = newSpeed;
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
    if (toTarget.Length() < actorSpeed)
    {
        actor->GetTransform()->SetWorldPosition(path.at(0)->Center);
        path.erase(path.begin());
    }
    else
    {
        toTarget.Normalize();
        actor->GetTransform()->AddWorldPosition(toTarget * actorSpeed);
    }
}

