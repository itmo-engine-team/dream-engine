#pragma once

#include "SimpleMath.h"
#include "GameObject/Component/SceneComponent.h"

using namespace DirectX::SimpleMath;

class Engine;

class CameraComponent : public SceneComponent
{
public:

    CameraComponent(Engine* engine, Actor* actor,
        Vector3 position = Vector3::Zero, Vector3 direction = Vector3::UnitZ);

    Matrix GetViewMatrix() const;
    Matrix GetProjectionMatrix() const;

protected:

    Matrix projectionMatrix;
    Vector3 direction;

};
