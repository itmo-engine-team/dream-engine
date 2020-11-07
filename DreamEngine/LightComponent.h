#pragma once

#include "SimpleMath.h"
#include "SceneComponent.h"

using namespace DirectX::SimpleMath;

class Game;

class LightComponent : public SceneComponent
{
public:

    LightComponent(Game* game, Actor* actor, Vector3 position = Vector3::Zero, Vector3 direction = Vector3::UnitZ);

    Matrix GetViewMatrix() const;
    Matrix GetProjectionMatrix() const;
    Vector3 GetDirection() const;

protected:

    Matrix projectionMatrix;
    Vector3 direction;

};
