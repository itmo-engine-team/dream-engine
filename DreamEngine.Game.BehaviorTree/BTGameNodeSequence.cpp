#include "BTGameNodeSequence.h"

BTGameNodeSequence::BTGameNodeSequence(BTGameNodeRoot* parentNode) : BTCompositeNode(parentNode)
{
}

BTGameNodeSequence::BTGameNodeSequence(BTCompositeNode* parentNode) : BTCompositeNode(parentNode)
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
