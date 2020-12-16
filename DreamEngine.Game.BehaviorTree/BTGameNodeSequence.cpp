#include "BTGameNodeSequence.h"

BTGameNodeSequence::BTGameNodeSequence(BTGameNode* parentNode) : BTCompositeNode(parentNode)
{
}

bool BTGameNodeSequence::Run()
{
    for (BTGameNode* gameNode : children)
    {
        iterator++;
        if (!gameNode->Run())
            return false;
    }
    return true;
}
