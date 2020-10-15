#pragma once

#include "ActorComponent.h"
#include "../../GameComponent/Transform.h"

class SceneComponent : public ActorComponent
{

public:

    SceneComponent(Game* game, Actor* actor, Transform* transform);

    Transform* GetTransform() const;

protected:

    Transform* transform;

};

