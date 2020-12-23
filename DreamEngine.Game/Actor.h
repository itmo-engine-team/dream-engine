#pragma once

#include <vector>

#include "GameObject.h"
#include "Transform.h"
#include "ActorComponentScene.h"
#include "ActorComponentFixed.h"
#include "SceneActorInfo.h"
#include "ActorContext.h"

class SceneActorInfo;

class Actor : public GameObject
{
public:

    Actor(ActorContext context, Transform* transform);

    void Init() override;
    void Update();
    void Draw();
    void DrawShadowMap();

    bool IsActive() const;

    const ActorContext& GetContext() const;
    Transform* GetTransform() const;

    void AddFixedComponent(ActorComponentFixed* component);
    void AddSceneComponent(ActorComponentScene* component);

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

    ActorContext context;
    Transform* transform;

    std::vector<ActorComponent*> components;
    std::vector<ActorComponentScene*> sceneComponents;
    std::vector<ActorComponentFixed*> fixedComponents;

    float actorDeltaTime;
    float actorDeltaTimeMultiplier = 1;
    
    virtual void onUpdate();

};

class ActorCreator
{

public:

    virtual ~ActorCreator() = default;

    virtual Actor* Create(ActorContext context, SceneActorInfo* actorInfo)
    {
        return new Actor(context, new Transform(actorInfo->GetTransformInfo()->GetPosition()));
    }

};