#pragma once

#include "ActorComponent.h"
#include "GameComponent/Transform.h"

class SceneComponent : public ActorComponent
{

public:

    SceneComponent(Engine* engine, Actor* actor, Transform* transform);

    Transform* GetTransform() const;

protected:

    Transform* transform;

};

