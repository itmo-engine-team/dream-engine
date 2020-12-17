#include "BTGameNodeSelector.h"

BTGameNodeSelector::BTGameNodeSelector(BTCompositeNode* parentNode) : BTCompositeNode(parentNode)
{
}

BTGameNodeSelector::BTGameNodeSelector(BTGameNodeRoot* parentNode) : BTCompositeNode(parentNode)
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
