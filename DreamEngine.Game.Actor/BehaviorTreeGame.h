#pragma once

#include "BTGameNodeRoot.h"

#include "Actor.h"

class BehaviorTreeGame
{

public:

    BehaviorTreeGame(Actor* actor);

    bool Update();
    BTGameNodeRoot* GetRootNode();
    Actor* GetActor();

protected:

    BTGameNodeRoot* rootNode;
    Actor* actor;
};
