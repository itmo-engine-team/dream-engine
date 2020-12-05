#pragma once

#include <DirectXCollision.h>

#include "Actor.h"

class Game;

class Gate : public Actor
{
public:

    Gate(Game* game, Transform* transform);

    DirectX::BoundingBox* collider;

protected:

    void onUpdate() override;

};
