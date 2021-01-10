#include "BTGReturnFalse.h"

BTGReturnFalse::BTGReturnFalse(BTGameNodeWithChild* parentNode, BehaviorTreeGame* behaviorTree) : BTGameNodeLogic(parentNode, behaviorTree)
{
}

bool BTGReturnFalse::Run()
{
    return false;
}
