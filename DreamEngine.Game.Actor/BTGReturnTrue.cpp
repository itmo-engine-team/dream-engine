#include "BTGReturnTrue.h"

BTGReturnTrue::BTGReturnTrue(BTGameNodeWithChild* parentNode, BehaviorTreeGame* behaviorTree) : BTGameNodeLogic(parentNode, behaviorTree)
{
}

bool BTGReturnTrue::Run()
{
    return true;
}
