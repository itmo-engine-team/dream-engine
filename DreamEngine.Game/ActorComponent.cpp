#include "ActorComponent.h"

ActorComponent::ActorComponent(ActorContext context, Actor* actor)
    : context(context), actor(actor)
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
