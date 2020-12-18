#pragma once

#include "SimpleMath.h"
#include "ActorComponentScene.h"

using namespace DirectX::SimpleMath;

class Game;

class CameraComponent : public ActorComponentScene
{
public:

    CameraComponent(Game* game, Actor* actor,
        Vector3 position = Vector3::Zero, Vector3 direction = Vector3::UnitZ);

    Matrix GetViewMatrix() const;
    Matrix GetProjectionMatrix() const;

protected:

    Matrix projectionMatrix;
    Vector3 direction;

};
