#pragma once

#include "Actor.h"
#include "SceneActorInfo.h"

class ActorFactory
{

public:

    static Actor* Create(ActorContext context, SceneActorInfo* actorInfo)
    {
        return creators[actorInfo->GetType()]->Create(context, actorInfo);
    }

protected:

    inline static std::unordered_map<ActorType, ActorCreator*> creators = {
        { ActorType::Actor , new ActorCreator() },
    };
    
};

