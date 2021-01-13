#pragma once

#include "ActorComponentFixed.h"

class ParamString;
class ParamBool;

class ACF_OnTargetCollision : public ActorComponentFixed
{

public:

    ACF_OnTargetCollision(Actor* actor);

protected:

    ParamString* targetTag;
    ParamBool* ignoreTriggerParam;

    std::vector<Actor*> targetActors;

    void onUpdate() override;

    virtual void onTargetCollision(Actor* targetActor) = 0;

};

