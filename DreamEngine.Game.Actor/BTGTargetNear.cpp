#include "BTGTargetNear.h"

#include "BehaviorTreeGame.h"
#include "ACF_TargetTag.h"
#include "Transform.h"

BTGTargetNear::BTGTargetNear(BTGameNodeWithChild* parentNode, BehaviorTreeGame* behaviorTree) : BTGameNodeLogic(parentNode, behaviorTree)
{
    ACF_TargetTag* targetTagAC = behaviorTree->GetActor()->FindComponent<ACF_TargetTag>();

    if (targetTagAC != nullptr)
    {
        targetActor = targetTagAC->GetTargetActor();
        fieldOfView = targetTagAC->GetFieldOfView();
    }
}

bool BTGTargetNear::Run()
{
    if (behaviorTree->IsLogging())
        printf("Target near \n");

    return checkTargetNear();
}

bool BTGTargetNear::checkTargetNear()
{
    float distance = Vector3::Distance(targetActor->GetTransform()->GetWorldPosition(), behaviorTree->GetActor()->GetTransform()->GetWorldPosition());

    if (distance <= fieldOfView)
        return true;

    return false;
}
