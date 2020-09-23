#pragma once

#include <DirectXCollision.h>
#include "Engine/Actor.h"

class Game;

class KatamariSphere : public Actor
{
public:

    KatamariSphere(Game* game, Transform* transform);

	DirectX::BoundingSphere* collider;

protected:

    void onUpdate() override;
    
};

