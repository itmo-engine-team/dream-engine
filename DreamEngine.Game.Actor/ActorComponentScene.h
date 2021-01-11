#pragma once

#include "ActorComponent.h"
#include "ActorComponentSceneInfo.h"
#include "TransformInfo.h"

class Transform;

class ActorComponentScene : public ActorComponent
{

public:

    ActorComponentScene(Actor* actor);
    virtual ~ActorComponentScene();

    Transform* GetTransform() const;

    void Draw();
    void DrawShadowMap();

    void UpdateTransform(TransformInfo* transformInfo);
    void UpdateTransform(const TransformInfo& transformInfo);

protected:

    Transform* transform;
    ParamTransform* transformParam;

    virtual void onDraw();
    virtual void onDrawShadowMap();

    void onParamUpdate(std::string name, BaseParam* param) override;
};

class ACS_Creator
{

public:

    virtual ~ACS_Creator() = default;

    virtual ActorComponentScene* Create(Actor* actor, ActorComponentSceneInfo* actorInfo) = 0;

};