#include "ACS_StaticModel.h"

#include "ConstantBuffer.h"
#include "LightBuffer.h"
#include "CameraBuffer.h"
#include "MeshObject.h"

#include "ACS_Light.h"
#include "ACS_Camera.h"
#include "Transform.h"
#include "AssetType.h"

ACS_StaticModel::ACS_StaticModel(ActorContext* context, Actor* actor,
                                 Transform* transform, ModelData* modelData)
    : ActorComponentScene(context, actor, transform), modelData(modelData)
{
    modelAssetParam = new ParamAsset(AssetType::Model);
    AddParam("modelAsset", modelAssetParam);
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
        meshObjects.push_back(new MeshObject(context->GetGraphics(), meshData));
    }
}

void ACS_StaticModel::onDraw()
{
    const ConstantBuffer cb =
    {
        transform->GetWorldMatrix(),
        context->GetCamera()->GetViewMatrix(),
        context->GetCamera()->GetProjectionMatrix(),
        context->GetLight()->GetViewMatrix(),
        context->GetLight()->GetProjectionMatrix(),
    };

    const LightBuffer lb =
    {
        Vector4{0.15f, 0.15f, 0.15f, 1.0f},
        Vector4{1.0f, 1.0f, 1.0f, 1.0f},
        context->GetLight()->GetDirection(),
        100.0f,
        {1.0f, 1.0f, 1.0f, 1.0f }
    };

    const CameraBuffer cameraBufferData =
    {
        context->GetCamera()->GetTransform()->GetWorldPosition()
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
        context->GetLight()->GetViewMatrix(),
        context->GetLight()->GetProjectionMatrix(),
    };
    for (auto meshObject : meshObjects)
    {
        meshObject->RenderShadowMap(cb);
    }
}

ActorComponentScene* ACS_Creator_StaticModel::Create(Actor* actor, ActorComponentSceneInfo* actorInfo)
{
    return new ACS_StaticModel(actor->GetContext(), actor,
        new Transform(actorInfo->GetTransformInfo()->GetPosition()), new ModelData());
}
