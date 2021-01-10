#include "BTGMoveTo.h"

#include "BehaviorTreeGame.h"
#include "ACF_Movement.h"

BTGMoveTo::BTGMoveTo(BTGameNodeWithChild* parentNode, BehaviorTreeGame* behaviorTree) : BTGameNodeLogic(parentNode, behaviorTree)
{
    if (behaviorTree->GetActor() != nullptr)
        movementComponent = behaviorTree->GetActor()->FindComponent<ACF_Movement>();
}

bool BTGMoveTo::Run()
{
    if (movementComponent == nullptr)
        return false;

    return movementComponent->MoveTo(target);
}

Vector3 BTGMoveTo::GetTargetLocation() const
{
    return target;
}

void BTGMoveTo::SetTargetPosition(Vector3 targetLocation)
{
    target = targetLocation;
}

float BTGMoveTo::GetReachRadius() const
{
    return reachRadius;
}

void BTGMoveTo::SetReachRadius(float reachRadius)
{
    this->reachRadius = reachRadius;
}
