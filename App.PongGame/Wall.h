#pragma once

#include <DirectXCollision.h>

#include "Actor.h"

class Game;

class Wall : public Actor
{
public:

    Wall(Game* game, Transform* transform);

    DirectX::BoundingBox* collider;

protected:

    void onUpdate() override;

};
