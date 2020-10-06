#pragma once

#include <DirectXCollision.h>

#include "GameObject/Actor.h"

class Engine;

class KatamariSphere : public Actor
{
public:

    KatamariSphere(Engine* engine, Transform* transform);

    DirectX::BoundingSphere* collider;

protected:

    void onUpdate() override;

};