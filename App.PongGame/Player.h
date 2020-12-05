#pragma once

#include <DirectXCollision.h>

#include "Actor.h"

class Game;

class Player : public Actor
{
public:

    Player(Game* game, Transform* transform);

    DirectX::BoundingBox* collider;

protected:

    void onUpdate() override;

};
