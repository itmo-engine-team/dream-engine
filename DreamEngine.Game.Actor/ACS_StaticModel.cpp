#include "ACS_StaticModel.h"

#include "ConstantBuffer.h"
#include "LightBuffer.h"
#include "CameraBuffer.h"
#include "MeshObject.h"

#include "ACS_Light.h"
#include "ACS_Camera.h"
#include "Transform.h"
#include "AssetType.h"
#include "ParamInt.h"

ACS_StaticModel::ACS_StaticModel(Actor* actor, ModelData* modelData)
    : ActorComponentScene(actor), modelData(modelData)
{
    modelAssetParam = new ParamAsset(AssetType::Model);
    AddParam("Model Asset", modelAssetParam);
    AddParam("Int", new ParamInt(0));
}

ACS_StaticModel::~ACS_StaticModel()
{
    delete transform;

    for (auto meshObject : meshObjects)
    {
        delete meshObject;
    }
}

void ACS_StaticModel::onInit()
{
    for (auto meshData : modelData->GetMeshDataList())
    {
        meshObjects.push_back(new MeshObject(actor->GetContext()->GetGraphics(), meshData));
    }
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
    if (param == modelAssetParam)
    {
        // TODO: Update model
    }
}

ActorComponentScene* ACS_Creator_StaticModel::Create(Actor* actor, ActorComponentSceneInfo* actorInfo)
{
    return new ACS_StaticModel(actor, new ModelData());
}
