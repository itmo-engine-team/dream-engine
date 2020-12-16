#include "BTGameNodeSelector.h"

BTGameNodeSelector::BTGameNodeSelector(BTGameNode* parentNode) : BTCompositeNode(parentNode)
{
}

bool BTGameNodeSelector::Run()
{
    for ( BTGameNode* gameNode : children)
    {
        iterator++;
        if (gameNode->Run())
            return true;
    }
    return false;
}
