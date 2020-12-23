#pragma once

#include "SimpleMath.h"
#include "ActorComponentScene.h"

using namespace DirectX::SimpleMath;

class Game;

class ACS_Light : public ActorComponentScene
{
public:

    ACS_Light(ActorContext* context, Actor* actor, Vector3 position = Vector3::Zero, Vector3 direction = Vector3::UnitZ);

    Matrix GetViewMatrix() const;
    Matrix GetProjectionMatrix() const;
    Vector3 GetDirection() const;

protected:

    Matrix projectionMatrix;
    Vector3 direction;

};
