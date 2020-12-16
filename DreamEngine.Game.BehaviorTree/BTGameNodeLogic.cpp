#include "BTGameNodeLogic.h"

BTGameNodeLogic::BTGameNodeLogic(BTGameNode* parentNode) : BTGameNode(parentNode)
{
}

bool BTGameNodeLogic::Run()
{
    return result;
}

