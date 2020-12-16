#include "SpectatorActor.h"

#include "Engine.h"

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
    if (!game->GetInputSystem()->IsMouseButtonPressed(MouseInput::Right)) return;

    // Rotation
    while (const auto delta = game->GetInputSystem()->ReadRawDelta())
    {
        Rotate(static_cast<float>(delta->x) * -game->GetGameDeltaTime(),
            static_cast<float>(delta->y) * game->GetGameDeltaTime());
    }

    // Movement
    if (game->GetInputSystem()->IsKeyPressed(KeyboardInput::Key_W))
    {
        Translate({ 0.0f, 0.0f, game->GetGameDeltaTime() });
    }
    if (game->GetInputSystem()->IsKeyPressed(KeyboardInput::Key_A))
    {
        Translate({ game->GetGameDeltaTime(), 0.0f, 0.0f });
    }
    if (game->GetInputSystem()->IsKeyPressed(KeyboardInput::Key_S))
    {
        Translate({ 0.0f, 0.0f, -game->GetGameDeltaTime() });
    }
    if (game->GetInputSystem()->IsKeyPressed(KeyboardInput::Key_D))
    {
        Translate({ -game->GetGameDeltaTime(), 0.0f, 0.0f });
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
