#pragma once

#include <vector>

#include "GameObject.h"

#include "SceneActorInfo.h"
#include "ActorContext.h"
#include "ParamExtender.h"
#include "TransformInfo.h"
#include "ParamTransform.h"

class Transform;
class ActorComponent;
class ActorComponentScene;
class ActorComponentFixed;

class Actor : public GameObject, ParamExtender
{
public:

    Actor(ActorContext* context);

    void Init() override;
    void Update();
    void Draw();
    void DrawShadowMap();

    bool IsActive() const;

    SceneActorInfo* GetActorInfo() const;
    ActorContext* GetContext() const;
    Transform* GetTransform() const;

    void AddFixedComponent(ActorComponentFixed* component);
    void AddSceneComponent(ActorComponentScene* component);

    void SetActorDeltaTimeMultiplier(float deltaTimeMultiplier);
    float GetActorDeltaTimeMultiplier();
    float GetActorDeltaTime();

    std::vector<ActorComponent*> GetComponents() const;

    template<class ComponentClass>
    ComponentClass* FindComponent()
    {
        for (auto component : components)
        {
            if (ComponentClass* castedComponent = dynamic_cast<ComponentClass*>(component))
            {
                return castedComponent;
            }
        }
        return nullptr;
    }

    template<class ComponentClass>
    std::vector<ComponentClass*> FindComponents()
    {
        auto foundComponents = std::vector<ComponentClass*>();
        for (auto component : components)
        {
            if (ComponentClass* castedComponent = dynamic_cast<ComponentClass*>(component))
            {
                foundComponents.push_back(castedComponent);
            }
        }
        return foundComponents;
    }

    bool RemoveComponent(ActorComponent* component);

    void UpdateTransform(TransformInfo* transformInfo);
    void UpdateTransform(const TransformInfo& transformInfo);

protected:

    SceneActorInfo* actorInfo;

    bool isActive = true;

    ActorContext* context;
    Transform* transform;
    ParamTransform* transformParam;

    std::vector<ActorComponent*> components;
    std::vector<ActorComponentScene*> sceneComponents;
    std::vector<ActorComponentFixed*> fixedComponents;

    float actorDeltaTime;
    float actorDeltaTimeMultiplier = 1;
    
    virtual void onUpdate();

    void onParamUpdate(std::string name, BaseParam* param) override;
};

class ActorCreator
{

public:

    virtual ~ActorCreator() = default;

    virtual Actor* Create(ActorContext* context, TransformInfo* transformInfo);

};