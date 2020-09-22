#pragma once

#include "GameObject.h"
#include "Transform.h"
#include "ActorComponent.h"

class Game;

class Actor : public GameObject
{
public:
	
	Actor(Game* game, Transform* transform);

	void Update();
	void Draw();

	Transform* GetTransform() const;

	void AddComponent(ActorComponent* component);

protected:

	Transform* transform;

	std::vector<ActorComponent*> components;

	virtual void onUpdate();

};

