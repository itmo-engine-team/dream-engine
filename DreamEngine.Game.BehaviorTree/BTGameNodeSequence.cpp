#include "BTGameNodeSequence.h"

BTGameNodeSequence::BTGameNodeSequence(BTGameNodeRoot* parentNode) : BTGameNodeComposite(parentNode)
{
}

BTGameNodeSequence::BTGameNodeSequence(BTGameNodeComposite* parentNode) : BTGameNodeComposite(parentNode)
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
