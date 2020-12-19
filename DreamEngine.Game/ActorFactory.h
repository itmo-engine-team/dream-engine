#pragma once

#include "Actor.h"
#include "ActorInfo.h"

class ActorFactory
{

public:

    static Actor* Create(const ActorInfo* actorInfo)
    {
        return creators[actorInfo->GetType()]->Create(actorInfo);
    }

protected:

    inline static std::unordered_map<ActorType, ActorCreator*> creators = {
        //{  ,  },
        
    };

};

