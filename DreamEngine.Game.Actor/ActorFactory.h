#pragma once

#include "Actor.h"
#include "SceneActorInfo.h"

class ActorFactory
{

public:

    static Actor* Create(ActorContext* context, ActorType type)
    {
        return creators[type]->Create(context);
    }

protected:

    inline static std::unordered_map<ActorType, ActorCreator*> creators = {
        { ActorType::Actor , new ActorCreator() },
    };
    
};

