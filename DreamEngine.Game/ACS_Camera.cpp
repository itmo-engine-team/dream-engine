#include "ACS_Camera.h"

#include "Game.h"
#include "Graphics.h"

ACS_Camera::ACS_Camera(Game* game, Actor* actor, Vector3 position, Vector3 direction)
    : ActorComponentScene(game, actor, new Transform(position)), direction(direction)
{
    projectionMatrix = Matrix::CreatePerspectiveFieldOfView(
        120,
        static_cast<float>(game->GetGraphics()->GetWindow()->GetScreenWidth()) 
            / static_cast<float>(game->GetGraphics()->GetWindow()->GetScreenHeight()),
        0.01f, 100.0f);
}

Matrix ACS_Camera::GetViewMatrix() const
{
    const Vector3 target = Vector3::Transform(direction, transform->GetWorldMatrix());
    return Matrix::CreateLookAt(transform->GetWorldPosition(), target, Vector3::UnitY);
}

Matrix ACS_Camera::GetProjectionMatrix() const
{
    return projectionMatrix;
}
