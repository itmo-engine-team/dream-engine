#pragma once

#include "ActorComponentScene.h"
#include "Transform.h"

class ACS_Collision : public ActorComponentScene
{

public:

    ACS_Collision(Actor* actor, Vector2 size);

    Vector2 GetSize();
    void SetSize(Vector2 newSize);

protected:

    Vector2 size;
};

class ACS_Creator_Collision : public ACS_Creator
{

public:

    ActorComponentScene* Create(Actor* actor, ActorComponentSceneInfo* actorInfo) override
    {
        return new ACS_Collision(actor, Vector2::One);
    }

};
