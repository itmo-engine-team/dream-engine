#include "BTGameNodeSelector.h"

BTGameNodeSelector::BTGameNodeSelector(BTGameNodeComposite* parentNode) : BTGameNodeComposite(parentNode)
{
}

BTGameNodeSelector::BTGameNodeSelector(BTGameNodeRoot* parentNode) : BTGameNodeComposite(parentNode)
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
