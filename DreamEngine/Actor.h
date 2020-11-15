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

    template<class ComponentClass>
    ComponentClass FindComponent()
    {
        for each (auto component in components)
        {
            if (ComponentClass castedComponent = dynamic_cast<ComponentClass>(component))
            {
                return castedComponent;
            }
        }
        return nullptr;
    }

    template<class ComponentClass>
    std::vector<ComponentClass> FindComponents()
    {
        auto foundComponents = std::vector<ComponentClass>();
        for each (auto component in components)
        {
            if (ComponentClass castedComponent = dynamic_cast<ComponentClass>(component))
            {
                foundComponents.push_back(castedComponent);
            }
        }
        return foundComponents;
    }

protected:

    bool isActive = true;

    Transform* transform;

    std::vector<ActorComponent*> components;

    float actorDeltaTime;
    float actorDeltaTimeMultiplier = 1;

    virtual void onUpdate();

};