#pragma once

#include "ActorComponentFixed.h"

class ParamString;

class ACF_Tag : public ActorComponentFixed
{

public:

    ACF_Tag() = delete;
    ACF_Tag(Actor* actor);

    std::string GetTag();

private:

    ParamString* tag;
};

class ACF_Creator_Tag : public ACF_Creator
{

public:

    ActorComponentFixed* Create(Actor* actor, ActorComponentFixedInfo* actorInfo) override
    {
        return new ACF_Tag(actor);
    }

};