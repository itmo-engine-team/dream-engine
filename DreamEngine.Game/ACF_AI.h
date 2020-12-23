#pragma once

#include "BehaviorTreeGame.h"
#include "ActorComponentFixed.h"

class ACF_AI : public ActorComponentFixed
{

public:

    ACF_AI(ActorContext* context, Actor* actor);

    BehaviorTreeGame* GetBehaviorTree();

private:

    BehaviorTreeGame* behaviorTree;
   
};

