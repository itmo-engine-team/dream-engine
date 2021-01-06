#include "Actor.h"

#include "SimpleMath.h"

#include "ActorComponentFixed.h"
#include "ActorComponentScene.h"
#include "DeltaTimeHandler.h"
#include "Transform.h"

using namespace DirectX::SimpleMath;

Actor::Actor(ActorContext* context, Transform* transform)
    : GameObject(), context(context), transform(transform)
{

}

void Actor::Init()
{
    GameObject::Init();

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

SceneActorInfo* Actor::GetActorInfo() const
{
    return actorInfo;
}

ActorContext* Actor::GetContext() const
{
    return context;
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
    actorDeltaTime = context->GetDeltaTimeHandler()->GetDeltaTime() * actorDeltaTimeMultiplier;
    return actorDeltaTime;
}

std::vector<ActorComponent*> Actor::GetComponents() const
{
    return components;
}

bool Actor::RemoveComponent(ActorComponent* component)
{
    bool isFound = false;
    for (auto it = components.begin(); it < components.end(); ++it)
    {
        if (*it == component)
        {
            isFound = true;
            components.erase(it);
            break;
        }
    }

    if (!isFound) return false;

    if (auto sceneComponent = dynamic_cast<ActorComponentScene*>(component))
    {
        for (auto it = sceneComponents.begin(); it < sceneComponents.end(); ++it)
        {
            if (*it == sceneComponent)
            {
                sceneComponents.erase(it);
                delete component;
                return true;
            }
        }
    }

    if (auto fixedComponent = dynamic_cast<ActorComponentFixed*>(component))
    {
        for (auto it = fixedComponents.begin(); it < fixedComponents.end(); ++it)
        {
            if (*it == fixedComponent)
            {
                fixedComponents.erase(it);
                delete component;
                return true;
            }
        }
    }

    return false;
}

void Actor::onUpdate()
{

}

Actor* ActorCreator::Create(ActorContext* context, TransformInfo* transformInfo)
{
    return new Actor(context, new Transform(transformInfo->GetPosition()));
}
