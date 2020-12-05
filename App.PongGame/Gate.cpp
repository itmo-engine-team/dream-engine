#include "Gate.h"

#include <iostream>
#include <SimpleMath.h>

Gate::Gate(Game* game, Transform* transform)
    : Actor(game, transform)
{
    collider = new DirectX::BoundingBox({ 0, 0, 0 }, { 0.1f, 0.5f, 4.2f });
}

void Gate::onUpdate()
{
    DirectX::SimpleMath::Vector3 worldPos = transform->GetWorldPosition();
    collider->Center = worldPos;
}
