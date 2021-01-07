#include "BTGameNodeSelector.h"

BTGameNodeSelector::BTGameNodeSelector(BTGameNodeWithChild* parentNode, BehaviorTreeGame* behaviorTree) : BTGameNodeComposite(parentNode , behaviorTree)
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
