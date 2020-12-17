#pragma once

#include "BehaviorTreeGame.h"
#include "ActorComponent.h"

class AIComponent : public ActorComponent
{

public:

    AIComponent(Game* game, Actor* actor);

    BehaviorTreeGame* GetBehaviorTree();

private:

    BehaviorTreeGame* behaviorTree;
   
};

