#include "ACS_StaticModel.h"

#include "ConstantBuffer.h"
#include "LightBuffer.h"
#include "CameraBuffer.h"
#include "MeshObject.h"

#include "ACS_Light.h"
#include "ACS_Camera.h"
#include "Transform.h"
#include "AssetType.h"
#include "GameAssetManager.h"

ACS_StaticModel::ACS_StaticModel(Actor* actor, ModelData* modelData, Texture* texture)
    : ActorComponentScene(actor), modelData(modelData), texture(texture)
{
    // Add params
    modelAssetParam = new ParamAsset(AssetType::Model);
    textureAssetParam = new ParamAsset(AssetType::Texture);
    AddParam("Model Asset", modelAssetParam);
    AddParam("Texture Asset", textureAssetParam);

    // Update model and texture
    hasManualModelData = modelData != nullptr;
    hasManualTexture = texture != nullptr;
}

ACS_StaticModel::~ACS_StaticModel()
{
    deleteMeshObjects();
}

void ACS_StaticModel::LoadModelData(ModelData* modelData)
{
    this->modelData = modelData;
    hasManualModelData = true;
    updateModel();
}

void ACS_StaticModel::LoadTexture(Texture* texture)
{
    this->texture = texture;
    hasManualTexture = true;
    updateTexture();
}

void ACS_StaticModel::deleteMeshObjects()
{
    for (auto meshObject : meshObjects)
    {
        delete meshObject;
    }
    meshObjects.clear();
}

void ACS_StaticModel::updateTexture()
{
    if (!hasManualTexture)
    {
        texture = textureAssetParam->IsDefault() ? nullptr
            : actor->GetContext()->GetGameAssetManager()->GetOrCreateTexture(textureAssetParam->Get());
    }

    for(auto meshObject : meshObjects)
    {
        meshObject->SetTexture(texture);
    }
}

void ACS_StaticModel::updateModel()
{
    if (!hasManualModelData)
    {
        modelData = modelAssetParam->IsDefault() ? nullptr
            : actor->GetContext()->GetGameAssetManager()->GetOrCreateModelData(modelAssetParam->Get());
    }

    deleteMeshObjects();
    if (modelData != nullptr)
    {
        for (auto meshData : modelData->GetMeshDataList())
        {
            meshObjects.push_back(new MeshObject(actor->GetContext()->GetGraphics(), meshData, texture));
        }
    }
}

void ACS_StaticModel::onInit()
{
    updateTexture();
    updateModel();
}

void ACS_StaticModel::onDraw()
{
    const ConstantBuffer cb =
    {
        transform->GetWorldMatrix(),
        actor->GetContext()->GetCamera()->GetViewMatrix(),
        actor->GetContext()->GetCamera()->GetProjectionMatrix(),
        actor->GetContext()->GetLight()->GetViewMatrix(),
        actor->GetContext()->GetLight()->GetProjectionMatrix(),
    };

    const LightBuffer lb =
    {
        Vector4{0.15f, 0.15f, 0.15f, 1.0f},
        Vector4{1.0f, 1.0f, 1.0f, 1.0f},
        actor->GetContext()->GetLight()->GetDirection(),
        100.0f,
        {1.0f, 1.0f, 1.0f, 1.0f }
    };

    const CameraBuffer cameraBufferData =
    {
        actor->GetContext()->GetCamera()->GetTransform()->GetWorldPosition()
    };

    for (auto meshObject : meshObjects)
    {
        meshObject->Render(cb, lb, cameraBufferData);
    }
}

void ACS_StaticModel::onDrawShadowMap()
{
    const ConstantBuffer cb =
    {
        transform->GetWorldMatrix(),
        actor->GetContext()->GetLight()->GetViewMatrix(),
        actor->GetContext()->GetLight()->GetProjectionMatrix(),
    };
    for (auto meshObject : meshObjects)
    {
        meshObject->RenderShadowMap(cb);
    }
}

void ACS_StaticModel::onParamUpdate(std::string name, BaseParam* param)
{
    ActorComponentScene::onParamUpdate(name, param);

    if (param == modelAssetParam)
    {
        hasManualModelData = false;
        updateModel();
    }

    if (param == textureAssetParam)
    {
        hasManualTexture = false;
        updateTexture();
    }
}

ActorComponentScene* ACS_Creator_StaticModel::Create(Actor* actor, ActorComponentSceneInfo* actorInfo)
{
    return new ACS_StaticModel(actor, new ModelData());
}
