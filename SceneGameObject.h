#pragma once
#include "Engine/GameObject.h"

class Game;

class SceneGameObject : public GameObject
{
public:
	SceneGameObject(Game* game, Vector3 position = Vector3::Zero);

	void init() override;
	void update() override;
	void draw() override;
};

