#include "BTGameNodeSequence.h"

BTGameNodeSequence::BTGameNodeSequence(BTGameNodeWithChild* parentNode, BehaviorTreeGame* behaviorTree) : BTGameNodeComposite(parentNode, behaviorTree)
{
}

bool BTGameNodeSequence::Run()
{
    for (BTGameNode* gameNode : children)
    {
        if (!gameNode->Run())
            return false;
    }
    return true;
}
