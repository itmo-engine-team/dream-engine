#include "Actor.h"

#include "Engine.h"
#include "SimpleMath.h"

using namespace DirectX::SimpleMath;

Actor::Actor(Game* game, Transform* transform)
    : GameObject(game), transform(transform)
{

}

void Actor::Update()
{
    onUpdate();

    // Update components
    for (auto component : components)
    {
        component->Update();
    }

    // Trigger event AfterUpdate
}

void Actor::Draw()
{
    // Draw components
    for (auto component : components)
    {
        component->Draw();
    }
}

void Actor::DrawShadowMap()
{
    // Draw shadow map for components
    for (auto component : components)
    {
        component->DrawShadowMap();
    }
}

Transform* Actor::GetTransform() const
{
    return transform;
}

void Actor::AddComponent(ActorComponent* component)
{
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

void Actor::onUpdate()
{

}