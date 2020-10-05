#include "SceneComponent.h"
#include "GameObject/Actor.h"

SceneComponent::SceneComponent(Engine* engine, Actor* actor, Transform* transform)
    : ActorComponent(engine, actor), transform(transform)
{
    transform->SetParent(actor->GetTransform(), true);
}

Transform* SceneComponent::GetTransform() const
{
    return transform;
}
