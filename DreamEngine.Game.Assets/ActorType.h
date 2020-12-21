#pragma once

#include <map>
#include <string>

enum class ActorType
{
    Actor,


    Unknown
};

const std::map<ActorType, std::string> MAP_ACTOR_TYPE_TO_STRING = {
    { ActorType::Actor, "Actor" }
};