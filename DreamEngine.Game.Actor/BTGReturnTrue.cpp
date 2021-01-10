#include "BTGReturnTrue.h"
#include "BehaviorTreeGame.h"

BTGReturnTrue::BTGReturnTrue(BTGameNodeWithChild* parentNode, BehaviorTreeGame* behaviorTree) : BTGameNodeLogic(parentNode, behaviorTree)
{
}

bool BTGReturnTrue::Run()
{
    if (behaviorTree->IsLogging())
        printf("ReturnTrue \n");

    return true;
}
