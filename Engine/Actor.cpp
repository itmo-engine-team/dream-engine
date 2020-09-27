#include "Engine.h"
#include "SimpleMath.h"
#include "Actor.h"


using namespace DirectX::SimpleMath;

Actor::Actor(Engine* engine, Transform* transform)
    : GameObject(engine), transform(transform)
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

void Actor::onUpdate()
{

}

Transform* Actor::GetTransform() const
{
    return transform;
}

void Actor::AddComponent(ActorComponent* component)
{
    components.push_back(component);
}
