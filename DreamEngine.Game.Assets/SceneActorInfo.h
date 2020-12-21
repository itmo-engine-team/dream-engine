#pragma once

#include "ActorType.h"
#include "TransformInfo.h"
#include "Serializable.h"

class SceneActorInfo : Serializable
{

public:

    SceneActorInfo(ActorType type);

    ActorType GetType() const;

    TransformInfo* GetTransformInfo() const;

protected:

    ActorType type = ActorType::Actor;

    TransformInfo* transformInfo;

    Json toJson() override;
    void fromJson(Json json) override;

};

