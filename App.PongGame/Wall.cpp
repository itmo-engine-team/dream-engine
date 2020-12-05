#include "Wall.h"

#include <iostream>
#include <SimpleMath.h>

Wall::Wall(Game* game, Transform* transform)
    : Actor(game, transform)
{
    collider = new DirectX::BoundingBox({ 0, 0, 0 }, { 5.5f, 0.1f, 0.1f });
}

void Wall::onUpdate()
{
    DirectX::SimpleMath::Vector3 worldPos = transform->GetWorldPosition();
    collider->Center = worldPos;
}
