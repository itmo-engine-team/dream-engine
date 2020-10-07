#include "SpectatorActor.h"

#include "Engine.h"

SpectatorActor::SpectatorActor(Engine* engine, Transform* transform) : Actor(engine, transform)
{
    cameraComponent = new CameraComponent(engine, this);
    AddComponent(cameraComponent);
}

CameraComponent* SpectatorActor::GetCameraComponent() const
{
    return cameraComponent;
}

void SpectatorActor::onUpdate()
{
    // Activates only with right button
    if (!engine->GetInputDevice()->KeyIsPressed('C')) return;

    // Rotation
    while (const auto delta = engine->GetMouse()->ReadRawDelta())
    {
        Rotate(static_cast<float>(delta->x) * -engine->GetDeltaTime(),
            static_cast<float>(delta->y) * engine->GetDeltaTime());
    }

    // Movement
    if (engine->GetInputDevice()->KeyIsPressed('W'))
    {
        Translate({ 0.0f, 0.0f, engine->GetDeltaTime() });
    }
    if (engine->GetInputDevice()->KeyIsPressed('A'))
    {
        Translate({ engine->GetDeltaTime(), 0.0f, 0.0f });
    }
    if (engine->GetInputDevice()->KeyIsPressed('S'))
    {
        Translate({ 0.0f, 0.0f, -engine->GetDeltaTime() });
    }
    if (engine->GetInputDevice()->KeyIsPressed('D'))
    {
        Translate({ -engine->GetDeltaTime(), 0.0f, 0.0f });
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
