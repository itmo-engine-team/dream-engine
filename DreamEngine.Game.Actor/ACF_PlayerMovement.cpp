#include "ACF_PlayerMovement.h"

#include "Transform.h"
#include "DeltaTimeHandler.h"
#include "ParamFloat.h"
#include "GameAssetManager.h"
#include "ACS_Collision.h"
#include "ParamBool.h"

ACF_PlayerMovement::ACF_PlayerMovement(Actor* actor) : ActorComponentFixed(actor)
{
    inputSystem = actor->GetContext()->GetInputSystem();

    speedParam = new ParamFloat(1);
    canMoveByDiagonalParam = new ParamBool();
    AddParam("Player Speed", speedParam);
    AddParam("Move by diagonal", canMoveByDiagonalParam);
}

float ACF_PlayerMovement::GetSpeed()
{
    return speedParam->Get();
}

void ACF_PlayerMovement::onInit()
{
    collisionComponent = actor->FindComponent<ACS_Collision>();
}

void ACF_PlayerMovement::onUpdate()
{
    // Skip if camera moves
    if (inputSystem->IsMouseButtonPressed(MouseInput::Right)) return;

    bool isInputX = false;
    bool isInputZ = false;
    Vector3 directionX;
    Vector3 directionZ;

    // Check Z movement with W or S keys
    if (inputSystem->IsKeyPressed(KeyboardInput::Key_W))
    {
        isInputZ = true;
        directionZ = Vector3::UnitZ;
    }
    else if (inputSystem->IsKeyPressed(KeyboardInput::Key_S))
    {
        isInputZ = true;
        directionZ = -Vector3::UnitZ;
    }

    // Check X movement with A or D keys
    if (inputSystem->IsKeyPressed(KeyboardInput::Key_A))
    {
        isInputX = true;
        directionX = Vector3::UnitX;
    }
    if (inputSystem->IsKeyPressed(KeyboardInput::Key_D))
    {
        isInputX = true;
        directionX = -Vector3::UnitX;
    }

    // Check if there is no input to handle
    if (!isInputX && !isInputZ) return;

    float speed = actor->GetContext()->GetDeltaTimeHandler()->GetDeltaTime() * speedParam->Get();
    Vector3 worldPosition = actor->GetTransform()->GetWorldPosition();

    // Check move by diagonal
    if (canMoveByDiagonalParam->Get() && isInputX && isInputZ)
    {
        Vector3 directionXZ = directionX + directionZ;
        directionXZ.Normalize();
        Vector3 newLocationXZ = worldPosition + directionXZ * speed;
        if (!actor->GetContext()->GetGameAssetManager()->
            IsAnyIntersectionWithCollision(newLocationXZ, collisionComponent->GetWorldSize(), actor, true))
        {
            actor->GetTransform()->AddWorldPosition(directionXZ * speed);
            return;
        }
    }
    
    if (isInputX)
    {
        Vector3 newLocationX = worldPosition + directionX * speed;
        if (!actor->GetContext()->GetGameAssetManager()->
            IsAnyIntersectionWithCollision(newLocationX, collisionComponent->GetWorldSize(), actor, true))
        {
            actor->GetTransform()->AddWorldPosition(directionX * speed);
            return;
        }
    }

    if (isInputZ)
    {
        Vector3 newLocationZ = worldPosition + directionZ * speed;
        if (!actor->GetContext()->GetGameAssetManager()->
            IsAnyIntersectionWithCollision(newLocationZ, collisionComponent->GetWorldSize(), actor, true))
        {
            actor->GetTransform()->AddWorldPosition(directionZ * speed);
            return;
        }
    }
    
}
