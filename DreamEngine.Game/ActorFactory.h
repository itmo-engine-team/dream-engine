#pragma once

#include "Actor.h"
#include "SceneActorInfo.h"

class ActorFactory
{

public:

    static Actor* Create(Game* game, SceneActorInfo* actorInfo)
    {
        return creators[actorInfo->GetType()]->Create(game, actorInfo);
    }

protected:

    inline static std::unordered_map<ActorType, ActorCreator*> creators = {
        { ActorType::Actor , new ActorCreator() },
    };
    
};

