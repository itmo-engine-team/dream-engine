#pragma once

#include <DirectXCollision.h>

#include "Actor.h"

namespace DirectX {
    namespace SimpleMath {
        struct Vector3;
    }
}

class Game;

class Ball : public Actor
{
public:

    const float SPEED = 75.0f;
    float SpeedX;
    float SpeedZ;
    bool isHitted = false;

    Ball(Game* game, Transform* transform);

    DirectX::BoundingSphere* collider;

    DirectX::SimpleMath::Vector3* Direction;

protected:

    void onUpdate() override;

};
