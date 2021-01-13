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
    bool IsLogging();

protected:

    BTGameNodeRoot* rootNode;
    Actor* actor;
    bool isLogging = true;

private:

    void initBehaviorTreeGame(BehaviorTreeEditor* behaviorTreeEditor);
};
