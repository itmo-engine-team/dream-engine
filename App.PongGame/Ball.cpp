#include "Ball.h"

#include <iostream>
#include <SimpleMath.h>

Ball::Ball(Game* game, Transform* transform)
    : Actor(game, transform)
{
    collider = new DirectX::BoundingSphere({ 0, 0, 0 }, 0.7f);
    Direction = new DirectX::SimpleMath::Vector3{ 1, 0, 1 };
}

void Ball::onUpdate()
{
    DirectX::SimpleMath::Vector3 worldPos = transform->GetWorldPosition();
    collider->Center = worldPos;

    float PosX = transform->GetWorldPosition().x + SpeedX * Direction->x;
    float PosZ = transform->GetWorldPosition().z + SpeedZ * Direction->z;
    transform->SetWorldPosition({ PosX, transform->GetWorldPosition().y, PosZ });
}

