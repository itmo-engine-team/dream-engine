#pragma once

#include "ActorComponentScene.h"
#include "ModelData.h"
#include "MeshObject.h"
#include "ParamAsset.h"

class Transform;

class ACS_StaticModel : public ActorComponentScene
{

public:

    ACS_StaticModel(Actor* actor, ModelData* modelData = nullptr, Texture* texture = nullptr);
    ~ACS_StaticModel() override;

    void LoadModelData(ModelData* modelData);
    void LoadTexture(Texture* texture);

protected:

    ParamAsset* modelAssetParam;
    ParamAsset* textureAssetParam;

    bool hasManualModelData;
    bool hasManualTexture;
    ModelData* modelData;
    Texture* texture;
    std::vector<MeshObject*> meshObjects;

    void deleteMeshObjects();
    void updateTexture();
    void updateModel();

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