#include "ActorContext.h"

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
