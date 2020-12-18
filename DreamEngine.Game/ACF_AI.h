#pragma once

#include "BehaviorTreeGame.h"
#include "ActorComponent.h"

class ACF_AI : public ActorComponent
{

public:

    ACF_AI(Game* game, Actor* actor);

    BehaviorTreeGame* GetBehaviorTree();

private:

    BehaviorTreeGame* behaviorTree;
   
};

