#pragma once

#include "BTGameNodeRoot.h"

class BehaviorTreeGame
{

protected:

    BTGameNodeRoot* rootNode;

public:

    BehaviorTreeGame(BTGameNodeRoot* rootNode);

    bool Update();
    BTGameNodeRoot* GetRootNode();
};
