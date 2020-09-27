#include "ActorComponent.h"

ActorComponent::ActorComponent(Engine* engine, Actor* actor)
    : engine(engine), actor(actor)
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


