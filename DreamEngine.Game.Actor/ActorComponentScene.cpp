#include "ActorComponentScene.h"

#include "Actor.h"
#include "Transform.h"

ActorComponentScene::ActorComponentScene(ActorContext* context, Actor* actor, Transform* transform)
    : ActorComponent(context, actor), transform(transform)
{
    transform->SetParent(actor->GetTransform(), true);
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

void ActorComponentScene::onDraw()
{

}

void ActorComponentScene::onDrawShadowMap()
{

}
