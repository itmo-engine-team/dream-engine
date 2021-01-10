#include "BTGReturnFalse.h"
#include "BehaviorTreeGame.h"

BTGReturnFalse::BTGReturnFalse(BTGameNodeWithChild* parentNode, BehaviorTreeGame* behaviorTree) : BTGameNodeLogic(parentNode, behaviorTree)
{
}

bool BTGReturnFalse::Run()
{
    if (behaviorTree->IsLogging())
        printf("RetrunFalse \n");

    return false;
}
