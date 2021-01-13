#include "ActorComponent.h"

ActorComponent::ActorComponent(Actor* actor)
    : actor(actor)
{

}

bool ActorComponent::IsActive() const
{
    return isActive && actor->IsActive();
}

void ActorComponent::SetActive(bool isActive)
{
    this->isActive = isActive;
}

Actor* ActorComponent::GetActor() const
{
    return actor;
}

void ActorComponent::Init()
{
    if (!IsActive()) return;

    onInit();
}

void ActorComponent::Update()
{
    if (!IsActive()) return;

    onUpdate();
}

void ActorComponent::onInit()
{

}

void ActorComponent::onUpdate()
{

}
