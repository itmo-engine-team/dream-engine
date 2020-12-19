#include "Actor.h"

#include "SimpleMath.h"

#include "Game.h"

using namespace DirectX::SimpleMath;

Actor::Actor(Game* game, Transform* transform)
    : GameObject(game), transform(transform)
{

}

void Actor::Init()
{
    onInit();

    // Update components
    for (auto component : components)
    {
        component->Init();
    }
}

void Actor::Update()
{
    onUpdate();

    // Update components
    for (auto component : components)
    {
        component->Update();
    }
}

void Actor::Draw()
{
    // Draw components
    for (auto component : sceneComponents)
    {
        component->Draw();
    }
}

void Actor::DrawShadowMap()
{
    // Draw shadow map for components
    for (auto component : sceneComponents)
    {
        component->DrawShadowMap();
    }
}

bool Actor::IsActive() const
{
    return isActive;
}

Transform* Actor::GetTransform() const
{
    return transform;
}

void Actor::AddFixedComponent(ActorComponentFixed* component)
{
    fixedComponents.push_back(component);
    components.push_back(component);
}

void Actor::AddSceneComponent(ActorComponentScene* component)
{
    sceneComponents.push_back(component);
    components.push_back(component);
}

void Actor::SetActorDeltaTimeMultiplier(float deltaTimeMultiplier)
{
    actorDeltaTimeMultiplier = std::clamp(deltaTimeMultiplier, 0.0f, 1.0f);
}

float Actor::GetActorDeltaTimeMultiplier()
{
    return actorDeltaTimeMultiplier;
}

float Actor::GetActorDeltaTime()
{
    actorDeltaTime = game->GetGameDeltaTime() * actorDeltaTimeMultiplier;
    return actorDeltaTime;
}

std::vector<ActorComponent*> Actor::GetComponents() const
{
    return components;
}

void Actor::onInit()
{
}

void Actor::onUpdate()
{

}
