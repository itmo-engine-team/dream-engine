#include "BTGameNodeLogic.h"

BTGameNodeLogic::BTGameNodeLogic(BTGameNodeRoot* parentNode) : BTGameNode(parentNode)
{
}

BTGameNodeLogic::BTGameNodeLogic(BTGameNodeComposite* parentNode) : BTGameNode(parentNode)
{
}

bool BTGameNodeLogic::Run()
{
    return TestCheckResult;
}

