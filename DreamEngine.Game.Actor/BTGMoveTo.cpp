#include "BTGMoveTo.h"

#include "BehaviorTreeGame.h"
#include "ACF_Movement.h"
#include "ACF_TargetReference.h"
#include "Transform.h"

BTGMoveTo::BTGMoveTo(BTGameNodeWithChild* parentNode, BehaviorTreeGame* behaviorTree) : BTGameNodeLogic(parentNode, behaviorTree)
{
    if (behaviorTree->GetActor() != nullptr)
        movementComponent = behaviorTree->GetActor()->FindComponent<ACF_Movement>();

    targetLocation = behaviorTree->GetActor()->GetTransform()->GetWorldPosition();
    targetActor = behaviorTree->GetActor()->FindComponent<ACF_TargetReference>()->GetTarget();
}

bool BTGMoveTo::Run()
{
    if (behaviorTree->IsLogging())
        printf("MoveTo \n");

    if (movementComponent == nullptr)
        return false;
 
    if (targetActor != nullptr)
        return movementComponent->MoveTo(targetActor->GetTransform()->GetWorldPosition());

    return movementComponent->MoveTo(targetLocation);
}

Vector3 BTGMoveTo::GetTargetLocation() const
{
    return targetLocation;
}

void BTGMoveTo::SetTargetLocation(Vector3 targetLocation)
{
    this->targetLocation = targetLocation;
}
