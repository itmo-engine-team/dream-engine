#include "BTGMoveTo.h"

#include "BehaviorTreeGame.h"
#include "ACF_Movement.h"

BTGMoveTo::BTGMoveTo(BTGameNodeRoot* parentNode, BehaviorTreeGame* behaviorTree) : BTGameNodeLogic(parentNode, behaviorTree)
{
    movementComponent = behaviorTree->GetActor()->FindComponent<ACF_Movement>();
}

BTGMoveTo::BTGMoveTo(BTGameNodeComposite* parentNode, BehaviorTreeGame* behaviorTree) : BTGameNodeLogic(parentNode, behaviorTree)
{
    movementComponent = behaviorTree->GetActor()->FindComponent<ACF_Movement>();
}

bool BTGMoveTo::Run()
{
    if (movementComponent == nullptr)
        return false;

    return movementComponent->MoveTo(target);
}

Vector3 BTGMoveTo::GetTargetLocation()
{
    return target;
}

void BTGMoveTo::SetTargetPosition(Vector3 targetLocation)
{
    target = targetLocation;
}