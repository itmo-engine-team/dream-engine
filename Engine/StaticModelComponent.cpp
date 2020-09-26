#include "StaticModelComponent.h"

StaticModelComponent::StaticModelComponent(Engine* engine, Actor* actor, Transform* transform, ModelData* modelData)
    : SceneComponent(engine, actor, transform), modelData(modelData)
{
    for (auto meshData : modelData->GetMeshDataList())
    {
        meshObjects.push_back(new MeshObject(engine, transform, meshData, modelData->GetShader()));
    }
}

void StaticModelComponent::onDraw()
{
    for (auto meshObject : meshObjects)
    {
        meshObject->Draw();
    }
}
