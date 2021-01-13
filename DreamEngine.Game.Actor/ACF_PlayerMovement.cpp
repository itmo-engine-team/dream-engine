#include "ACF_PlayerMovement.h"

#include "Transform.h"
#include "DeltaTimeHandler.h"
#include "ParamFloat.h"
#include "GameAssetManager.h"

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
        Vector3 newLocation = actor->GetTransform()->GetWorldPosition() + Vector3{ 0.0f, 0.0f, actor->GetContext()->GetDeltaTimeHandler()->GetDeltaTime() * speed->Get() };
        if (actor->GetContext()->GetGameAssetManager()->CheckCollisionsHit(newLocation, actor)) return;

        actor->GetTransform()->AddWorldPosition({ 0.0f, 0.0f, actor->GetContext()->GetDeltaTimeHandler()->GetDeltaTime() * speed->Get() });
    }
    if (inputSystem->IsKeyPressed(KeyboardInput::Key_A))
    {
        Vector3 newLocation = actor->GetTransform()->GetWorldPosition() + Vector3{ actor->GetContext()->GetDeltaTimeHandler()->GetDeltaTime() * speed->Get(), 0.0f, 0.0f };
        if (actor->GetContext()->GetGameAssetManager()->CheckCollisionsHit(newLocation, actor)) return;

        actor->GetTransform()->AddWorldPosition({ actor->GetContext()->GetDeltaTimeHandler()->GetDeltaTime() * speed->Get(), 0.0f, 0.0f });
    }
    if (inputSystem->IsKeyPressed(KeyboardInput::Key_S))
    {
        Vector3 newLocation = actor->GetTransform()->GetWorldPosition() + Vector3{ 0.0f, 0.0f, -actor->GetContext()->GetDeltaTimeHandler()->GetDeltaTime() * speed->Get() };
        if (actor->GetContext()->GetGameAssetManager()->CheckCollisionsHit(newLocation, actor)) return;

        actor->GetTransform()->AddWorldPosition({ 0.0f, 0.0f, -actor->GetContext()->GetDeltaTimeHandler()->GetDeltaTime() * speed->Get() });
    }
    if (inputSystem->IsKeyPressed(KeyboardInput::Key_D))
    {
        Vector3 newLocation = actor->GetTransform()->GetWorldPosition() + Vector3{ -actor->GetContext()->GetDeltaTimeHandler()->GetDeltaTime() * speed->Get(), 0.0f, 0.0f};
        if (actor->GetContext()->GetGameAssetManager()->CheckCollisionsHit(newLocation, actor)) return;

        actor->GetTransform()->AddWorldPosition({ -actor->GetContext()->GetDeltaTimeHandler()->GetDeltaTime() * speed->Get(), 0.0f, 0.0f });
    }
}
