#pragma once

#include "Actor.h"

class ActorComponent : public ParamExtender
{

public:

    ActorComponent(Actor* actor);
    virtual ~ActorComponent() = default;

    void Init();
    void Update();

protected:

    Actor* actor;

    virtual void onInit();
    virtual void onUpdate();

};

