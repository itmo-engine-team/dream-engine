#pragma once

#include "ActorComponent.h"
#include "ActorComponentFixedInfo.h"

class ActorComponentFixed : public ActorComponent
{

public:

    ActorComponentFixed(Actor* actor);

};

class ACF_Creator
{

public:

    virtual ~ACF_Creator() = default;

    virtual ActorComponentFixed* Create(Actor* actor, ActorComponentFixedInfo* actorInfo) = 0;

};