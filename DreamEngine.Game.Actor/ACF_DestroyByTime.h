#pragma once

#include "ActorComponentFixed.h"

class ParamFloat;

class ACF_DestroyByTime : public ActorComponentFixed
{

public:

    ACF_DestroyByTime(Actor* actor);

protected:

    ParamFloat* timeToDestroyParam;

    float currentTimeToDestroy;

    void onInit() override;
    void onUpdate() override;

};

class ACF_Creator_DestroyByTime : public ACF_Creator
{

public:

    ActorComponentFixed* Create(Actor* actor, ActorComponentFixedInfo* actorInfo) override
    {
        return new ACF_DestroyByTime(actor);
    }

};