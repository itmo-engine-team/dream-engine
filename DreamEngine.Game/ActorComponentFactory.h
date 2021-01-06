#pragma once

#include "ActorComponentSceneInfo.h"
#include "ActorComponentFixedInfo.h"
#include "ActorComponent.h"
#include "ACS_Light.h"
#include "ACF_AI.h"
#include "ACS_StaticModel.h"

class ActorComponentFactory
{

public:

    static ActorComponentScene* CreateSceneComponent(Actor* actor, ActorComponentSceneInfo* componentInfo)
    {
        return sceneComponentCreators[componentInfo->GetType()]->Create(actor, componentInfo);
    }

    static ActorComponentFixed* CreateFixedComponent(Actor* actor, ActorComponentFixedInfo* componentInfo)
    {
        return fixedComponentCreators[componentInfo->GetType()]->Create(actor, componentInfo);
    }

protected:

    inline static std::unordered_map<ACS_Type, ACS_Creator*> sceneComponentCreators = {
        { ACS_Type::StaticModel, new ACS_Creator_StaticModel() },
        { ACS_Type::Collision, new ACS_Creator_StaticModel() },
    };

    inline static std::unordered_map<ACF_Type, ACF_Creator*> fixedComponentCreators = {
        { ACF_Type::AI , new ACF_Creator_AI() },
    };
    
};
