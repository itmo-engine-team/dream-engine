#pragma once

#include "ActorComponent.h"
#include "Transform.h"

class ActorComponentScene : public ActorComponent
{

public:

    ActorComponentScene(Game* game, Actor* actor, Transform* transform);

    Transform* GetTransform() const;

    void Draw();
    void DrawShadowMap();

protected:

    Transform* transform;

    virtual void onDraw();
    virtual void onDrawShadowMap();

};

