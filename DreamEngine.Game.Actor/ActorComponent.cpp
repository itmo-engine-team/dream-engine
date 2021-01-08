#include "ActorComponent.h"

ActorComponent::ActorComponent(Actor* actor)
    : actor(actor)
{

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
