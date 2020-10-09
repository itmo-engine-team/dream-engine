#pragma once

#include "GameObject.h"
#include "GameComponent/Transform.h"
#include "Component/ActorComponent.h"

class Game;

class Actor : public GameObject
{
public:

    Actor(Game* Game, Transform* transform);

    void Update();
    void Draw();

    Transform* GetTransform() const;

    void AddComponent(ActorComponent* component);
    void SetActorDeltaTimeMultiplier(float deltaTimeMultiplier);
    float GetActorDeltaTime();

protected:

    Transform* transform;

    std::vector<ActorComponent*> components;

    float actorDeltaTime = 1;
    float actorDeltaTimeMultiplier = 1;

    virtual void onUpdate();

};