#include "ActorComponentScene.h"

#include "Actor.h"
#include "Transform.h"

ActorComponentScene::ActorComponentScene(Actor* actor) : ActorComponent(actor)
{
    transform = new Transform();
    transform->SetParent(actor->GetTransform(), true);

    transformParam = new ParamTransform();
    AddParam("Transform", transformParam);
}

ActorComponentScene::~ActorComponentScene()
{
    delete transform;
}

Transform* ActorComponentScene::GetTransform() const
{
    return transform;
}

void ActorComponentScene::Draw()
{
    onDraw();
}

void ActorComponentScene::DrawShadowMap()
{
    onDrawShadowMap();
}

void ActorComponentScene::UpdateTransform(TransformInfo* transformInfo)
{
    transform->SetLocalPosition(transformInfo->GetPosition());
    transform->SetLocalRotation(transformInfo->GetRotation());
}

void ActorComponentScene::UpdateTransform(const TransformInfo& transformInfo)
{
    transform->SetLocalPosition(transformInfo.GetPosition());
    transform->SetLocalRotation(transformInfo.GetRotation());
}

void ActorComponentScene::onDraw()
{

}

void ActorComponentScene::onDrawShadowMap()
{

}

void ActorComponentScene::onParamUpdate(std::string name, BaseParam* param)
{
    ActorComponent::onParamUpdate(name, param);

    if (param == transformParam)
    {
        UpdateTransform(transformParam->Get());
    }
}
