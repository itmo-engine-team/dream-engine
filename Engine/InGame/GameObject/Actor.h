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
    float GetActorDeltaTimeMultiplier();

protected:

    Transform* transform;

    std::vector<ActorComponent*> components;

    float actorDeltaTime;
    float actorDeltaTimeMultiplier = 1;

    virtual void onUpdate();

};