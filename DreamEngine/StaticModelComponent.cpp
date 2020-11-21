#include "StaticModelComponent.h"

#include "Game.h"

StaticModelComponent::StaticModelComponent(Game* game, Actor* actor, Transform* transform, ModelData* modelData)
    : SceneComponent(game, actor, transform), modelData(modelData)
{
    for (auto meshData : modelData->GetMeshDataList())
    {
        meshObjects.push_back(new MeshObject(game->GetEngine(), transform, meshData, modelData->GetShader()));
    }
}

void StaticModelComponent::onDraw()
{
    for (auto meshObject : meshObjects)
    {
        meshObject->RenderDeferred();
    }
}

void StaticModelComponent::onDrawShadowMap()
{
    for (auto meshObject : meshObjects)
    {
        meshObject->RenderShadowMap();
    }
}

void StaticModelComponent::onRenderDeferred()
{
    for (auto meshObject : meshObjects)
    {
        meshObject->RenderLight();
    }
}
