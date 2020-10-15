#include "SceneComponent.h"
#include "../../GameObject/Actor.h"

SceneComponent::SceneComponent(Game* game, Actor* actor, Transform* transform)
    : ActorComponent(game, actor), transform(transform)
{
    transform->SetParent(actor->GetTransform(), true);
}

Transform* SceneComponent::GetTransform() const
{
    return transform;
}
