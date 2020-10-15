#include "CameraComponent.h"

#include "../../../Engine.h"

CameraComponent::CameraComponent(Game* game, Actor* actor, Vector3 position, Vector3 direction)
    : SceneComponent(game, actor, new Transform(position)), direction(direction)
{
    projectionMatrix = Matrix::CreatePerspectiveFieldOfView(
        120,
        static_cast<float>(game->GetEngine()->GetScreenWidth()) 
            / static_cast<float>(game->GetEngine()->GetScreenHeight()),
        0.01f, 100.0f);
}

Matrix CameraComponent::GetViewMatrix() const
{
    const Vector3 target = Vector3::Transform(direction, transform->GetWorldMatrix());
    return Matrix::CreateLookAt(transform->GetWorldPosition(), target, Vector3::UnitY);
}

Matrix CameraComponent::GetProjectionMatrix() const
{
    return projectionMatrix;
}
