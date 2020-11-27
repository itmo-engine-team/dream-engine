#include "StaticModelComponent.h"

#include "Game.h"
#include "Engine.h"
#include "ConstantBuffer.h"
#include "LightBuffer.h"
#include "CameraBuffer.h"
#include "MeshObject.h"

StaticModelComponent::StaticModelComponent(Game* game, Actor* actor,
    Transform* transform, ModelData* modelData)
    : SceneComponent(game, actor, transform), modelData(modelData)
{
    for (auto meshData : modelData->GetMeshDataList())
    {
        meshObjects.push_back(new MeshObject(
            game->GetEngine()->GetGraphics(), meshData, modelData->GetShader()));
    }
}

void StaticModelComponent::onDraw()
{
    const ConstantBuffer cb =
    {
        transform->GetWorldMatrix(),
        game->GetCamera()->GetViewMatrix(),
        game->GetCamera()->GetProjectionMatrix(),
        game->GetLight()->GetViewMatrix(),
        game->GetLight()->GetProjectionMatrix(),
    };

    const LightBuffer lb =
    {
        Vector4{0.15f, 0.15f, 0.15f, 1.0f},
        Vector4{1.0f, 1.0f, 1.0f, 1.0f},
        game->GetLight()->GetDirection(),
        100.0f,
        {1.0f, 1.0f, 1.0f, 1.0f }
    };

    const CameraBuffer cameraBufferData =
    {
        game->GetCamera()->GetTransform()->GetWorldPosition()
    };

    for (auto meshObject : meshObjects)
    {
        meshObject->Render(cb, lb, cameraBufferData);
    }
}

void StaticModelComponent::onDrawShadowMap()
{
    const ConstantBuffer cb =
    {
        transform->GetWorldMatrix(),
        game->GetLight()->GetViewMatrix(),
        game->GetLight()->GetProjectionMatrix(),
    };
    for (auto meshObject : meshObjects)
    {
        meshObject->RenderShadowMap(cb);
    }
}
