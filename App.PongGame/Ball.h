#pragma once

#include <DirectXCollision.h>

#include "Actor.h"

class Game;

class Ball : public Actor
{
public:

    Ball(Game* game, Transform* transform);

    DirectX::BoundingSphere* collider;

protected:

    void onUpdate() override;

};
