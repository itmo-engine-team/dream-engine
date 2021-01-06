#include "BTGameNodeSequence.h"

BTGameNodeSequence::BTGameNodeSequence(BTGameNodeRoot* parentNode, BehaviorTreeGame* behaviorTree) : BTGameNodeComposite(parentNode, behaviorTree)
{
}

BTGameNodeSequence::BTGameNodeSequence(BTGameNodeComposite* parentNode, BehaviorTreeGame* behaviorTree) : BTGameNodeComposite(parentNode, behaviorTree)
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
