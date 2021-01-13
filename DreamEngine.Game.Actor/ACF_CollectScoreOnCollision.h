#pragma once

#include "ACF_DestroyTargetOnCollision.h"

class ParamInt;

class ACF_CollectScoreOnCollision : public ACF_DestroyTargetOnCollision
{

public:

    ACF_CollectScoreOnCollision(Actor* actor);

protected:

    ParamInt* scoreOnCollectParam;

    void onTargetCollision(Actor* targetActor) override;

};

class ACF_Creator_CollectScoreOnCollision : public ACF_Creator
{

public:

    ActorComponentFixed* Create(Actor* actor, ActorComponentFixedInfo* actorInfo) override
    {
        return new ACF_CollectScoreOnCollision(actor);
    }

};