#pragma once

#include "SimpleMath.h"
#include "ActorType.h"

using namespace DirectX::SimpleMath;

class ActorInfo
{

public:

    ActorInfo(ActorType type);

    ActorType GetType() const;

protected:

    ActorType type = ActorType::Unknown;

    Vector3 position;

};

