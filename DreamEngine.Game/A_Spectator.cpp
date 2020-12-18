#include "A_Spectator.h"

#include "Game.h"

A_Spectator::A_Spectator(Game* game, Transform* transform) : Actor(game, transform)
{
    cameraComponent = new ACS_Camera(game, this);
    AddComponent(cameraComponent);
}

ACS_Camera* A_Spectator::GetCameraComponent() const
{
    return cameraComponent;
}

void A_Spectator::onUpdate()
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

void A_Spectator::Rotate(const float dx, const float dy) const
{
    transform->AddLocalRotation(Vector3::UnitY, dx * rotationSpeed);
    transform->AddLocalRotation(Vector3::UnitX, dy * rotationSpeed);
}

void A_Spectator::Translate(const Vector3 translation) const
{
    transform->AddLocalPosition(translation * moveSpeed);
}
