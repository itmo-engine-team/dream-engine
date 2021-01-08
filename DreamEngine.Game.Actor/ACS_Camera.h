#pragma once

#include "SimpleMath.h"
#include "ActorComponentScene.h"

using namespace DirectX::SimpleMath;

class ACS_Camera : public ActorComponentScene
{
public:

    ACS_Camera(Actor* actor, Vector3 direction = Vector3::UnitZ);

    Matrix GetViewMatrix() const;
    Matrix GetProjectionMatrix() const;

protected:

    Matrix projectionMatrix;
    Vector3 direction;

};
