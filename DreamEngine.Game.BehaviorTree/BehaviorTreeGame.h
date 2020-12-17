#pragma once

#include "BTGameNodeRoot.h"

class BehaviorTreeGame
{

public:

    BehaviorTreeGame();

    bool Update();
    BTGameNodeRoot* GetRootNode();

protected:

    BTGameNodeRoot* rootNode;
};
