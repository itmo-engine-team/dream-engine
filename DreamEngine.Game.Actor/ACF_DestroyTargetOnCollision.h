#pragma once

#include "ACF_OnTargetCollision.h"

class ACF_DestroyTargetOnCollision : public ACF_OnTargetCollision
{

public:

    ACF_DestroyTargetOnCollision(Actor* actor);

protected:

    void onTargetCollision(Actor* targetActor) override;

};

class ACF_Creator_DestroyTargetOnCollision : public ACF_Creator
{

public:

    ActorComponentFixed* Create(Actor* actor, ActorComponentFixedInfo* actorInfo) override
    {
        return new ACF_DestroyTargetOnCollision(actor);
    }

};