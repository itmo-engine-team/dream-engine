#pragma once

#include "ActorComponentFixed.h"

class ParamFloat;

class ACF_ActorSpawner : public ActorComponentFixed
{

public:

    ACF_ActorSpawner(Actor* actor);

protected:

    ParamAsset* spawnAsset;
    ParamFloat* timeToSpawn;
    ParamFloat* timeToStart;
    ParamFloat* randomDistribution;

    float currentTimeToSpawn;

    void onInit() override;
    void onUpdate() override;

};

class ACF_Creator_ActorSpawner : public ACF_Creator
{

public:

    ActorComponentFixed* Create(Actor* actor, ActorComponentFixedInfo* actorInfo) override
    {
        return new ACF_ActorSpawner(actor);
    }

};