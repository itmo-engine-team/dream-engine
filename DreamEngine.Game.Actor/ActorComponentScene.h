#pragma once

#include "ActorComponent.h"
#include "ActorComponentSceneInfo.h"

class Transform;

class ActorComponentScene : public ActorComponent
{

public:

    ActorComponentScene(Actor* actor, Transform* transform);

    Transform* GetTransform() const;

    void Draw();
    void DrawShadowMap();

protected:

    Transform* transform;

    virtual void onDraw();
    virtual void onDrawShadowMap();

};

class ACS_Creator
{

public:

    virtual ~ACS_Creator() = default;

    virtual ActorComponentScene* Create(Actor* actor, ActorComponentSceneInfo* actorInfo) = 0;

};