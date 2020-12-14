#include "BTGameNodeSelector.h"

bool BTGameNodeSelector::Run()
{
    for ( BTGameNode* gameNode : children)
    {
        if (gameNode->Run())
            return true;
    }
    return false;
}
