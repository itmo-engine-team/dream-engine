#pragma once

#include "SimpleMath.h"
#include "ActorType.h"
#include "TransformInfo.h"

using namespace DirectX::SimpleMath;

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

