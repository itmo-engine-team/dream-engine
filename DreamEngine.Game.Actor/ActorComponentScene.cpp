#include "ActorComponentScene.h"

#include "Actor.h"
#include "Transform.h"

ActorComponentScene::ActorComponentScene(Actor* actor) : ActorComponent(actor)
{
    transform = new Transform();
    transform->SetParent(actor->GetTransform(), true);
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
}

void ActorComponentScene::onDraw()
{

}

void ActorComponentScene::onDrawShadowMap()
{

}
