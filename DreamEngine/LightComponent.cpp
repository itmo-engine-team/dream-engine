#include "LightComponent.h"

#include "Engine.h"

LightComponent::LightComponent(Game* game, Actor* actor, Vector3 position, Vector3 direction)
    : SceneComponent(game, actor, new Transform(position)), direction(direction)
{
    projectionMatrix = Matrix::CreatePerspectiveFieldOfView(
        DirectX::XM_PIDIV2, 1.0f, 12.0f, 50.0f);
}

Matrix LightComponent::GetViewMatrix() const
{
    const Vector3 target = Vector3::Transform(direction, transform->GetWorldMatrix());
    return Matrix::CreateLookAt(transform->GetWorldPosition(), target, Vector3::UnitY);
}

Matrix LightComponent::GetProjectionMatrix() const
{
    return projectionMatrix;
}
