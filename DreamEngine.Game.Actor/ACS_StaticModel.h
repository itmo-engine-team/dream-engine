#pragma once

#include "ActorComponentScene.h"
#include "ModelData.h"
#include "MeshObject.h"

class Transform;

class ACS_StaticModel : public ActorComponentScene
{

public:

    ACS_StaticModel(ActorContext* context, Actor* actor, Transform* transform, ModelData* modelData);
    ~ACS_StaticModel();

protected:

    ModelData* modelData;

    std::vector<MeshObject*> meshObjects;

    void onDraw() override;
    void onDrawShadowMap() override;

};

class ACS_Creator_StaticModel : public ACS_Creator
{

public:

    ActorComponentScene* Create(Actor* actor, ActorComponentSceneInfo* actorInfo) override;

};