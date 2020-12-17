#pragma once

#include "BTGameNodeRoot.h"

class BehaviorTreeGame
{

protected:

    BTGameNodeRoot* rootNode;

public:

    BehaviorTreeGame();

    bool Update();
    BTGameNodeRoot* GetRootNode();
};
