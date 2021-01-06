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

class ACF_Creator_AI : public ACF_Creator
{

public:

    ActorComponentFixed* Create(Actor* actor, ActorComponentFixedInfo* actorInfo) override
    {
        return new ACF_AI(actor->GetContext(), actor);
    }

};

