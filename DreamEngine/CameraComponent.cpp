#include "CameraComponent.h"

#include "Engine.h"
#include "Graphics.h"

CameraComponent::CameraComponent(Game* game, Actor* actor, Vector3 position, Vector3 direction)
    : SceneComponent(game, actor, new Transform(position)), direction(direction)
{
    projectionMatrix = Matrix::CreatePerspectiveFieldOfView(
        120,
        static_cast<float>(game->GetGraphics()->GetWindow()->GetScreenWidth()) 
            / static_cast<float>(game->GetGraphics()->GetWindow()->GetScreenHeight()),
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
