#pragma once

#include "BTGameNodeRoot.h"
#include "Actor.h"

class BehaviorTreeEditor;

class BehaviorTreeGame
{

public:

    BehaviorTreeGame(Actor* actor, BehaviorTreeEditor* behaviorTreeEditor);

    bool Update();
    BTGameNodeRoot* GetRootNode();
    Actor* GetActor();

protected:

    BTGameNodeRoot* rootNode;
    Actor* actor;

private:

    void initBehaviorTreeGame(BehaviorTreeEditor* behaviorTreeEditor);
};
