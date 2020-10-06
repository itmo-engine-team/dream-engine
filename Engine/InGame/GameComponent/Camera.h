#pragma once

#include "SimpleMath.h"
#include "GameComponent/Transform.h"

class Engine;
using namespace DirectX::SimpleMath;

class Camera
{
public:

    Camera(Engine* engine, Vector3 position, Vector3 direction = { 0, 0, 1 });
    ~Camera() = default;

    Matrix GetViewMatrix();
    Matrix GetProjectionMatrix() const;

    void Rotate(float dx, float dy);
    void Translate(Vector3 translation);
    virtual void Update();

    Transform transform;

protected:

    Vector3 direction;

    float rotationSpeed = 0.1;
    float moveSpeed = 5;

    Matrix projectionMatrix;

};
