#pragma once

#include "ActorComponentFixed.h"

class ParamFloat;
class ParamBool;
class ACS_Collision;

class ACF_PlayerMovement : public ActorComponentFixed
{

public:

    ACF_PlayerMovement(Actor* actor);

    float GetSpeed();

protected:

    InputSystem* inputSystem;
    ParamFloat* speedParam;
    ParamBool* canMoveByDiagonalParam;
    ACS_Collision* collisionComponent;

    void onInit() override;
    void onUpdate() override;

};

class ACF_Creator_PlayerMovement : public ACF_Creator
{

public:

    ActorComponentFixed* Create(Actor* actor, ActorComponentFixedInfo* actorInfo) override
    {
        return new ACF_PlayerMovement(actor);
    }

};