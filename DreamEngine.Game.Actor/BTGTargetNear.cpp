#include "BTGTargetNear.h"

#include "BehaviorTreeGame.h"
#include "ACF_TargetTag.h"
#include "Transform.h"

BTGTargetNear::BTGTargetNear(BTGameNodeWithChild* parentNode, BehaviorTreeGame* behaviorTree) : BTGameNodeLogic(parentNode, behaviorTree)
{
    targetTagAC = behaviorTree->GetActor()->FindComponent<ACF_TargetTag>();
}

bool BTGTargetNear::Run()
{
    if (behaviorTree->IsLogging())
        printf("Target near \n");

    return checkTargetNear();
}

bool BTGTargetNear::checkTargetNear()
{
    float distance = Vector3::Distance(
        targetTagAC->GetTargetActor()->GetTransform()->GetWorldPosition(),
        behaviorTree->GetActor()->GetTransform()->GetWorldPosition());

    if (distance <= targetTagAC->GetFieldOfView())
        return true;

    return false;
}
