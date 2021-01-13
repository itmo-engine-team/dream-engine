#pragma once

#include "ActorComponentFixed.h"

class ParamFloat;

class ACF_PlayerMovement : public ActorComponentFixed
{

public:

    ACF_PlayerMovement(Actor* actor);

    float GetSpeed();

protected:

    void onUpdate() override;

    InputSystem* inputSystem;
    ParamFloat* speed;
};

class ACF_Creator_PlayerMovement : public ACF_Creator
{

public:

    ActorComponentFixed* Create(Actor* actor, ActorComponentFixedInfo* actorInfo) override
    {
        return new ACF_PlayerMovement(actor);
    }

};