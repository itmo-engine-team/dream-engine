#include "ACS_Light.h"
#include "Transform.h"

ACS_Light::ACS_Light(ActorContext* context, Actor* actor, Vector3 position, Vector3 direction)
    : ActorComponentScene(context, actor, new Transform(position)), direction(direction)
{
    projectionMatrix = Matrix::CreateOrthographic(10, 10, 0.1f, 100);
}

Matrix ACS_Light::GetViewMatrix() const
{
    const Vector3 target = -Vector3::Transform(direction, transform->GetWorldMatrix());
    return Matrix::CreateLookAt(transform->GetWorldPosition(), target, Vector3::UnitY);
}

Matrix ACS_Light::GetProjectionMatrix() const
{
    return projectionMatrix;
}

Vector3 ACS_Light::GetDirection() const
{
    auto v = -Vector3::Transform(direction, transform->GetWorldMatrix());
    v.Normalize();
    return v;
}
