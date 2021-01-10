#include "ACF_PlayerMovement.h"

#include "Transform.h"
#include "DeltaTimeHandler.h"

ACF_PlayerMovement::ACF_PlayerMovement(Actor* actor) : ActorComponentFixed(actor)
{
    inputSystem = actor->GetContext()->GetInputSystem();
}

void ACF_PlayerMovement::onUpdate()
{
    // Skip if camera moves
    if (inputSystem->IsMouseButtonPressed(MouseInput::Right)) return;

    // Update sphere movement
    if (inputSystem->IsKeyPressed(KeyboardInput::Key_W))
    {
        actor->GetTransform()->AddWorldPosition({ 0.0f, 0.0f, actor->GetContext()->GetDeltaTimeHandler()->GetDeltaTime() });
    }
    if (inputSystem->IsKeyPressed(KeyboardInput::Key_A))
    {
        actor->GetTransform()->AddWorldPosition({ actor->GetContext()->GetDeltaTimeHandler()->GetDeltaTime(), 0.0f, 0.0f });
    }
    if (inputSystem->IsKeyPressed(KeyboardInput::Key_S))
    {
        actor->GetTransform()->AddWorldPosition({ 0.0f, 0.0f, -actor->GetContext()->GetDeltaTimeHandler()->GetDeltaTime() });
    }
    if (inputSystem->IsKeyPressed(KeyboardInput::Key_D))
    {
        actor->GetTransform()->AddWorldPosition({ -actor->GetContext()->GetDeltaTimeHandler()->GetDeltaTime(), 0.0f, 0.0f });
    }
}
