#include "ActorContext.h"

#include "NavMesh.h"

Graphics* ActorContext::GetGraphics() const
{
    return graphics;
}

InputSystem* ActorContext::GetInputSystem() const
{
    return inputSystem;
}

DeltaTimeHandler* ActorContext::GetDeltaTimeHandler() const
{
    return deltaTimeHandler;
}

AssetManager* ActorContext::GetAssetManager() const
{
    return assetManager;
}

ACS_Light* ActorContext::GetLight() const
{
    return light;
}

void ActorContext::SetLight(ACS_Light* lightComponent)
{
    light = lightComponent;
}

ACS_Camera* ActorContext::GetCamera() const
{
    return camera;
}

void ActorContext::SetCamera(ACS_Camera* cameraComponent)
{
    camera = cameraComponent;
}

NavMesh* ActorContext::GetNavMesh() const
{
    return navMesh;
}

void ActorContext::SetNavMesh(NavMesh* newNavMesh)
{
    navMesh = newNavMesh;
}

bool ActorContext::IsGameMode() const
{
    return isGameMode;
}

void ActorContext::SetGameMode(bool isGameMode)
{
    this->isGameMode = isGameMode;
}
