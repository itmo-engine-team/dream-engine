#include "SceneComponent.h"
#include "Actor.h"

SceneComponent::SceneComponent(Engine* engine, Actor* actor, Transform* transform)
    : ActorComponent(engine, actor), transform(transform)
{
    transform->SetParent(actor->GetTransform());
}

Transform* SceneComponent::GetTransform() const
{
    return transform;
}
