#pragma once

#include "Actor.h"

class ActorComponent
{

public:

    ActorComponent(ActorContext* context, Actor* actor);
    virtual ~ActorComponent() = default;

    void Init();
    void Update();

protected:

    ActorContext* context;
    Actor* actor;

    virtual void onInit();
    virtual void onUpdate();

};

