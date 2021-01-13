#pragma once

#include "ACF_OnTargetCollision.h"

class ACF_GameOverOnTargetCollision : public ACF_OnTargetCollision
{

public:

    ACF_GameOverOnTargetCollision(Actor* actor);

protected:

    void onTargetCollision(Actor* targetActor) override;

};

class ACF_Creator_GameOverOnTargetCollision : public ACF_Creator
{

public:

    ActorComponentFixed* Create(Actor* actor, ActorComponentFixedInfo* actorInfo) override
    {
        return new ACF_GameOverOnTargetCollision(actor);
    }

};

