#include "Ball.h"

#include <iostream>
#include <SimpleMath.h>

Ball::Ball(Game* game, Transform* transform)
    : Actor(game, transform)
{
    collider = new DirectX::BoundingSphere({ 0, 0, 0 }, 0.7);
}

void Ball::onUpdate()
{
    DirectX::SimpleMath::Vector3 worldPos = transform->GetWorldPosition();
    collider->Center = worldPos;
}
