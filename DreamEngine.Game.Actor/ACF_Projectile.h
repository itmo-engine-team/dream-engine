#pragma once

#include "ActorComponentFixed.h"

class ParamVector3;
class ParamFloat;

class ACF_Projectile : public ActorComponentFixed
{

public:

    ACF_Projectile(Actor* actor);

protected:

    ParamVector3* directionParam;
    ParamFloat* speedParam;

    void onUpdate() override;

};

class ACF_Creator_Projectile : public ACF_Creator
{

public:

    ActorComponentFixed* Create(Actor* actor, ActorComponentFixedInfo* actorInfo) override
    {
        return new ACF_Projectile(actor);
    }

};