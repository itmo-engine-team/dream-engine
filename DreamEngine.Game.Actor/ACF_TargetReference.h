#pragma once

#include "ActorComponentFixed.h"

class ACF_TargetReference : public ActorComponentFixed
{

public:

    ACF_TargetReference(Actor* actor, Actor* targetRef = nullptr);

    Actor* GetTarget();
    void SetTarget(Actor* targetRef);

protected:

    Actor* targetRef;
};

