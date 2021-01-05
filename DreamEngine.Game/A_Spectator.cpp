#include "A_Spectator.h"

A_Spectator::A_Spectator(ActorContext* context, Transform* transform) : Actor(context, transform)
{
    cameraComponent = new ACS_Camera(context, this);
    AddSceneComponent(cameraComponent);
}

ACS_Camera* A_Spectator::GetCameraComponent() const
{
    return cameraComponent;
}

void A_Spectator::onUpdate()
{
    // Activates only with right button
    if (!context->GetInputSystem()->IsMouseButtonPressed(MouseInput::Right)) return;

    // Rotation
    while (const auto delta = context->GetInputSystem()->ReadRawDelta())
    {
        Rotate(static_cast<float>(delta->x) * -context->GetDeltaTimeHandler()->GetDeltaTime(),
            static_cast<float>(delta->y) * context->GetDeltaTimeHandler()->GetDeltaTime());
    }

    // Movement
    if (context->GetInputSystem()->IsKeyPressed(KeyboardInput::Key_W))
    {
        Translate({ 0.0f, 0.0f, context->GetDeltaTimeHandler()->GetDeltaTime() });
    }
    if (context->GetInputSystem()->IsKeyPressed(KeyboardInput::Key_A))
    {
        Translate({ context->GetDeltaTimeHandler()->GetDeltaTime(), 0.0f, 0.0f });
    }
    if (context->GetInputSystem()->IsKeyPressed(KeyboardInput::Key_S))
    {
        Translate({ 0.0f, 0.0f, -context->GetDeltaTimeHandler()->GetDeltaTime() });
    }
    if (context->GetInputSystem()->IsKeyPressed(KeyboardInput::Key_D))
    {
        Translate({ -context->GetDeltaTimeHandler()->GetDeltaTime(), 0.0f, 0.0f });
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
