#include "Player.h"

#include <iostream>
#include <SimpleMath.h>

Player::Player(Game* game, Transform* transform)
    : Actor(game, transform)
{
    collider = new DirectX::BoundingBox({ 0, 0, 0 }, { 0.1f, 0.1f, 0.5f });
}

void Player::onUpdate()
{
    DirectX::SimpleMath::Vector3 worldPos = transform->GetWorldPosition();
    collider->Center = worldPos;
}
