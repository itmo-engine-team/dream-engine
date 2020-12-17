#include "BTGameNodeLogic.h"

BTGameNodeLogic::BTGameNodeLogic(BTGameNodeRoot* parentNode) : BTGameNode(parentNode)
{
}

BTGameNodeLogic::BTGameNodeLogic(BTCompositeNode* parentNode) : BTGameNode(parentNode)
{
}

bool BTGameNodeLogic::Run()
{
    return result;
}

