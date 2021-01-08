#include "ACS_Camera.h"

#include "Graphics.h"
#include "Transform.h"

ACS_Camera::ACS_Camera(Actor* actor, Vector3 direction) : ActorComponentScene(actor), direction(direction)
{
    projectionMatrix = Matrix::CreatePerspectiveFieldOfView(
        120,
        static_cast<float>(actor->GetContext()->GetGraphics()->GetWindow()->GetScreenWidth()) 
            / static_cast<float>(actor->GetContext()->GetGraphics()->GetWindow()->GetScreenHeight()),
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
