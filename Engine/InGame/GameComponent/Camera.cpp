#include "Camera.h"

#include "Engine.h"

Camera::Camera(Engine* engine, Vector3 position, Vector3 direction) : direction(direction)
{
    Transform.SetWorldPosition(position);

    projectionMatrix = Matrix::CreatePerspectiveFieldOfView(
        120,
        static_cast<float>(engine->GetScreenWidth()) / static_cast<float>(engine->GetScreenHeight()),
        0.01f, 100.0f);
}

Matrix Camera::GetViewMatrix()
{
    Vector3 target = Vector3::Transform(direction, Transform.GetWorldMatrix());
    Vector3 up = { 0, 1, 0 };
    return Matrix::CreateLookAt(Transform.GetWorldPosition(), target, up);
}

Matrix Camera::GetProjectionMatrix() const
{
    return projectionMatrix;
}

void Camera::Rotate(float dx, float dy)
{
    Transform.AddLocalRotation(Vector3::UnitY, dx * rotationSpeed);
    Transform.AddLocalRotation(Vector3::UnitX, dy * rotationSpeed);
}

void Camera::Translate(Vector3 translation)
{
    Transform.AddLocalPosition(translation);
}

void Camera::Update()
{
}
