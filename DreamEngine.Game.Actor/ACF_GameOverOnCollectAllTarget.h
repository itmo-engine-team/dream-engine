#pragma once

#include "ActorComponentFixed.h"

class ParamString;

class ACF_GameOverOnCollectAllTarget : public ActorComponentFixed
{

public:

    ACF_GameOverOnCollectAllTarget(Actor* actor);

protected:

    ParamString* targetTag;

    void onUpdate() override;

};

class ACF_Creator_GameOverOnCollectAllTarget : public ACF_Creator
{

public:

    ActorComponentFixed* Create(Actor* actor, ActorComponentFixedInfo* actorInfo) override
    {
        return new ACF_GameOverOnCollectAllTarget(actor);
    }

};

