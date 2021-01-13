#include "ACF_PlayerMovement.h"

#include "Transform.h"
#include "DeltaTimeHandler.h"
#include "ParamFloat.h"

ACF_PlayerMovement::ACF_PlayerMovement(Actor* actor) : ActorComponentFixed(actor)
{
    inputSystem = actor->GetContext()->GetInputSystem();

    speed = new ParamFloat(1);
    AddParam("Player Speed", speed);
}

float ACF_PlayerMovement::GetSpeed()
{
    return speed->Get();
}

void ACF_PlayerMovement::onUpdate()
{
    // Skip if camera moves
    if (inputSystem->IsMouseButtonPressed(MouseInput::Right)) return;

    // Update sphere movement
    if (inputSystem->IsKeyPressed(KeyboardInput::Key_W))
    {
        actor->GetTransform()->AddWorldPosition({ 0.0f, 0.0f, actor->GetContext()->GetDeltaTimeHandler()->GetDeltaTime() * speed->Get() });
    }
    if (inputSystem->IsKeyPressed(KeyboardInput::Key_A))
    {
        actor->GetTransform()->AddWorldPosition({ actor->GetContext()->GetDeltaTimeHandler()->GetDeltaTime() * speed->Get(), 0.0f, 0.0f });
    }
    if (inputSystem->IsKeyPressed(KeyboardInput::Key_S))
    {
        actor->GetTransform()->AddWorldPosition({ 0.0f, 0.0f, -actor->GetContext()->GetDeltaTimeHandler()->GetDeltaTime() * speed->Get() });
    }
    if (inputSystem->IsKeyPressed(KeyboardInput::Key_D))
    {
        actor->GetTransform()->AddWorldPosition({ -actor->GetContext()->GetDeltaTimeHandler()->GetDeltaTime() * speed->Get(), 0.0f, 0.0f });
    }
}
