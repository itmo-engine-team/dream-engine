#pragma once

#include "BehaviorTreeGame.h"
#include "ActorComponentFixed.h"

class ACF_AI : public ActorComponentFixed
{

public:

    ACF_AI(Game* game, Actor* actor);

    BehaviorTreeGame* GetBehaviorTree();

private:

    BehaviorTreeGame* behaviorTree;
   
};

