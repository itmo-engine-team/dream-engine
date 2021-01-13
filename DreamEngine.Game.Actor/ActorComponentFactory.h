#pragma once

#include "ActorComponentSceneInfo.h"
#include "ActorComponentFixedInfo.h"
#include "ActorComponent.h"
#include "ACS_Light.h"
#include "ACF_AI.h"
#include "ACF_Tag.h"
#include "ACF_TargetTag.h"
#include "ACF_Movement.h"
#include "ACF_PlayerMovement.h"
#include "ACS_StaticModel.h"
#include "ACS_Collision.h"

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
        { ACS_Type::Collision, new ACS_Creator_Collision() },
    };

    inline static std::unordered_map<ACF_Type, ACF_Creator*> fixedComponentCreators = {
        { ACF_Type::AI , new ACF_Creator_AI() },
        { ACF_Type::Tag , new ACF_Creator_Tag() },
        { ACF_Type::TargetTag , new ACF_Creator_TargetTag() },
        { ACF_Type::Movement , new ACF_Creator_Movement() },
        { ACF_Type::PlayerMovement , new ACF_Creator_PlayerMovement() },
    };
    
};
