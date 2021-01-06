#include "BTGameNodeSelector.h"

BTGameNodeSelector::BTGameNodeSelector(BTGameNodeComposite* parentNode, BehaviorTreeGame* behaviorTree) : BTGameNodeComposite(parentNode , behaviorTree)
{
}

BTGameNodeSelector::BTGameNodeSelector(BTGameNodeRoot* parentNode, BehaviorTreeGame* behaviorTree) : BTGameNodeComposite(parentNode, behaviorTree)
{
}

bool BTGameNodeSelector::Run()
{
    for (BTGameNode* gameNode : children)
    {
        if (gameNode->Run())
            return true;
    }
    return false;
}
