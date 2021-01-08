#pragma once

#include "ActorComponentScene.h"
#include "ModelData.h"
#include "MeshObject.h"
#include "ParamAsset.h"

class Transform;

class ACS_StaticModel : public ActorComponentScene
{

public:

    ACS_StaticModel(Actor* actor, Transform* transform, ModelData* modelData);
    ~ACS_StaticModel();

protected:

    ParamAsset* modelAssetParam;

    ModelData* modelData;

    std::vector<MeshObject*> meshObjects;

    void onInit() override;
    void onDraw() override;
    void onDrawShadowMap() override;

    void onParamUpdate(std::string name, BaseParam* param) override;

};

class ACS_Creator_StaticModel : public ACS_Creator
{

public:

    ActorComponentScene* Create(Actor* actor, ActorComponentSceneInfo* actorInfo) override;

};