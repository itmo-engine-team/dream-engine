#include "SceneComponent.h"
#include "Actor.h"

SceneComponent::SceneComponent(Game* game, Actor* actor, Transform* transform)
    : ActorComponent(game, actor), transform(transform)
{
    transform->SetParent(actor->GetTransform());
}

Transform* SceneComponent::GetTransform() const
{
    return transform;
}
