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
    void setActorDeltaTime(float deltaMultiplier);

protected:

    Transform* transform;

    std::vector<ActorComponent*> components;

    float actorDeltaTime = 0;
    float actorDeltaTimeMultiplier = 0;

    virtual void onUpdate();
    float GetActorDeltaTime();
};

