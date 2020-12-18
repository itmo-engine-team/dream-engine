#include "ActorComponentScene.h"
#include "Actor.h"

ActorComponentScene::ActorComponentScene(Game* game, Actor* actor, Transform* transform)
    : ActorComponent(game, actor), transform(transform)
{
    transform->SetParent(actor->GetTransform(), true);
}

Transform* ActorComponentScene::GetTransform() const
{
    return transform;
}
