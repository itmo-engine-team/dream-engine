#pragma once

#include "Actor.h"

class ActorComponent : public ParamExtender
{

public:

    ActorComponent(Actor* actor);
    virtual ~ActorComponent() = default;

    Actor* GetActor() const;
    bool IsActive() const;
    void SetActive(bool isActive);

    void Init();
    void Update();

protected:

    Actor* actor;
    bool isActive = true;

    virtual void onInit();
    virtual void onUpdate();

};

