#pragma once

#include "ActorComponent.h"
#include "Transform.h"

class ActorComponentScene : public ActorComponent
{

public:

    ActorComponentScene(Game* game, Actor* actor, Transform* transform);

    Transform* GetTransform() const;

protected:

    Transform* transform;

};

