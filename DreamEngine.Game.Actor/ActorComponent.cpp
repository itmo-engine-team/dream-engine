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
    onInit();
    // Trigger event AfterInit
}

void ActorComponent::Update()
{
    onUpdate();
    // Trigger event AfterUpdate
}

void ActorComponent::onInit()
{

}

void ActorComponent::onUpdate()
{

}
