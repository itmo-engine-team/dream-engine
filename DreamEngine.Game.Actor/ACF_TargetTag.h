#pragma once

#include "ActorComponentFixed.h"

class ParamString;
class ParamFloat;

class ACF_TargetTag : public ActorComponentFixed
{

public:

    ACF_TargetTag() = delete;
    ACF_TargetTag(Actor* actor);

    Actor* GetTargetActor();
    float GetFieldOfView();

protected:

    void onInit() override;
    void findTargetActor();

private:

    ParamString* targetTag;
    Actor* targetActor;
    ParamFloat* fieldOfView;
};

class ACF_Creator_TargetTag : public ACF_Creator
{

public:

    ActorComponentFixed* Create(Actor* actor, ActorComponentFixedInfo* actorInfo) override
    {
        return new ACF_TargetTag(actor);
    }

};