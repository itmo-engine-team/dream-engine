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

class ACS_Creator_Collision : public ACS_Creator
{

public:

    ActorComponentScene* Create(Actor* actor, ActorComponentSceneInfo* actorInfo) override
    {
        return new ACS_Collision(actor->GetContext(), actor,
            new Transform(actorInfo->GetTransformInfo()->GetPosition()), Vector2::One);
    }

};
