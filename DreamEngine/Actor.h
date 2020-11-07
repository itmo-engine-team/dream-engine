#pragma once

#include <vector>

#include "GameObject.h"
#include "Transform.h"
#include "ActorComponent.h"

class Game;

class Actor : public GameObject
{
public:

    Actor(Game* Game, Transform* transform);

    void Update();
    void Draw();
    void DrawShadowMap();

    bool IsActive() const;

    Transform* GetTransform() const;

    void AddComponent(ActorComponent* component);

    void SetActorDeltaTimeMultiplier(float deltaTimeMultiplier);
    float GetActorDeltaTimeMultiplier();
    float GetActorDeltaTime();

    std::vector<ActorComponent*> GetComponents() const;

    template<class C>
    C FindComponent() 
    {
        for each (auto component in components)
        {
            if (C castedComponent = dynamic_cast<C>(component))
            {
                return castedComponent;
            }
        }
        return nullptr;
    }

    template<class C>
    std::vector<C> FindComponents()
    {
        auto foundComponents = std::vector<C>();
        for each (auto component in components)
        {
            if (C castedComponent = dynamic_cast<C>(component))
            {
                foundComponents.push_back(castedComponent);
            }
        }
        return foundComponents;
    }

protected:

    bool isActive;

    Transform* transform;

    std::vector<ActorComponent*> components;

    float actorDeltaTime;
    float actorDeltaTimeMultiplier = 1;

    virtual void onUpdate();

};