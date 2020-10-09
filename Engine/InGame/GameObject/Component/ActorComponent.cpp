#include "ActorComponent.h"

ActorComponent::ActorComponent(Game* game, Actor* actor)
    : game(game), actor(actor)
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

void ActorComponent::Draw()
{
    onDraw();
}

void ActorComponent::onInit()
{

}

void ActorComponent::onUpdate()
{

}

void ActorComponent::onDraw()
{
}


