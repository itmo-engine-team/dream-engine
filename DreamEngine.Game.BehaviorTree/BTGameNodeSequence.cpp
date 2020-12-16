#include "BTGameNodeSequence.h"

bool BTGameNodeSequence::Run()
{
    for (BTGameNode* gameNode : children)
    {
        if (!gameNode->Run())
            return false;
    }
    return true;
}
