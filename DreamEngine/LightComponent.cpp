#include "LightComponent.h"

#include "Engine.h"

LightComponent::LightComponent(Game* game, Actor* actor, Vector3 position, Vector3 direction)
    : SceneComponent(game, actor, new Transform(position)), direction(direction)
{
    projectionMatrix = Matrix::CreateOrthographic(20, 20, 0.1f, 100);
}

Matrix LightComponent::GetViewMatrix() const
{
    const Vector3 target = -Vector3::Transform(direction, transform->GetWorldMatrix());
    return Matrix::CreateLookAt(transform->GetWorldPosition(), target, Vector3::UnitY);
}

Matrix LightComponent::GetProjectionMatrix() const
{
    return projectionMatrix;
}

Vector3 LightComponent::GetDirection() const
{
    auto v = -Vector3::Transform(direction, transform->GetWorldMatrix());
    v.Normalize();
    return v;
}
