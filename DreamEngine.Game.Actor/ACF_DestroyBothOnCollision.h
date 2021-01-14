#pragma once

#include "ACF_DestroyTargetOnCollision.h"

class ACF_DestroyBothOnCollision : public ACF_DestroyTargetOnCollision
{

public:

    ACF_DestroyBothOnCollision(Actor* actor);

protected:

    void onTargetCollision(Actor* targetActor) override;

};

class ACF_Creator_DestroyBothOnCollision : public ACF_Creator
{

public:

    ActorComponentFixed* Create(Actor* actor, ActorComponentFixedInfo* actorInfo) override
    {
        return new ACF_DestroyBothOnCollision(actor);
    }

};