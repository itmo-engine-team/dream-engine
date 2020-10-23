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

    Transform* GetTransform() const;

    void AddComponent(ActorComponent* component);

    void SetActorDeltaTimeMultiplier(float deltaTimeMultiplier);
    float GetActorDeltaTimeMultiplier();
    float GetActorDeltaTime();

protected:

    Transform* transform;

    std::vector<ActorComponent*> components;

    float actorDeltaTime;
    float actorDeltaTimeMultiplier = 1;

    virtual void onUpdate();

};