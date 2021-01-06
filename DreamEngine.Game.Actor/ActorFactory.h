#pragma once

#include "Actor.h"
#include "SceneActorInfo.h"

class ActorFactory
{

public:

    static Actor* Create(ActorContext* context, ActorType type, TransformInfo* transformInfo)
    {
        return creators[type]->Create(context, transformInfo);
    }

protected:

    inline static std::unordered_map<ActorType, ActorCreator*> creators = {
        { ActorType::Actor , new ActorCreator() },
    };
    
};

