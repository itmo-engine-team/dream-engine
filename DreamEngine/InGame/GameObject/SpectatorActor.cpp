#include "SpectatorActor.h"

#include "../../Engine.h"

SpectatorActor::SpectatorActor(Game* game, Transform* transform) : Actor(game, transform)
{
    cameraComponent = new CameraComponent(game, this);
    AddComponent(cameraComponent);
}

CameraComponent* SpectatorActor::GetCameraComponent() const
{
    return cameraComponent;
}

void SpectatorActor::onUpdate()
{
    // Activates only with right button
    if (!game->GetEngine()->GetInputDevice()->KeyIsPressed('C')) return;

    // Rotation
    while (const auto delta = game->GetEngine()->GetMouse()->ReadRawDelta())
    {
        Rotate(static_cast<float>(delta->x) * -game->GetEngine()->GetDeltaTime(),
            static_cast<float>(delta->y) * game->GetEngine()->GetDeltaTime());
    }

    // Movement
    if (game->GetEngine()->GetInputDevice()->KeyIsPressed('W'))
    {
        Translate({ 0.0f, 0.0f, game->GetEngine()->GetDeltaTime() });
    }
    if (game->GetEngine()->GetInputDevice()->KeyIsPressed('A'))
    {
        Translate({ game->GetEngine()->GetDeltaTime(), 0.0f, 0.0f });
    }
    if (game->GetEngine()->GetInputDevice()->KeyIsPressed('S'))
    {
        Translate({ 0.0f, 0.0f, -game->GetEngine()->GetDeltaTime() });
    }
    if (game->GetEngine()->GetInputDevice()->KeyIsPressed('D'))
    {
        Translate({ -game->GetEngine()->GetDeltaTime(), 0.0f, 0.0f });
    }
}

void SpectatorActor::Rotate(const float dx, const float dy) const
{
    transform->AddLocalRotation(Vector3::UnitY, dx * rotationSpeed);
    transform->AddLocalRotation(Vector3::UnitX, dy * rotationSpeed);
}

void SpectatorActor::Translate(const Vector3 translation) const
{
    transform->AddLocalPosition(translation * moveSpeed);
}
