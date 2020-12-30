#pragma once

#include "ActorComponentScene.h"

class ACS_Collision : public ActorComponentScene
{

public:

    ACS_Collision(ActorContext* context, Actor* actor, Transform* transform, Vector2 size);

    Vector2 GetSize();
    void SetSize(Vector2 newSize);

protected:

    Vector2 size;
};

