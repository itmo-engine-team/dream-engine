#pragma once

#include "ActorType.h"
#include "TransformInfo.h"

class SceneActorInfo
{

public:

    SceneActorInfo(ActorType type);

    ActorType GetType() const;

    TransformInfo* GetTransformInfo() const;

protected:

    ActorType type = ActorType::Actor;

    TransformInfo* transformInfo;

};

