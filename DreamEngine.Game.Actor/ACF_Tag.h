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

