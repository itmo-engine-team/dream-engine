#include "BaseSceneViewer.h"

#include "A_Light.h"
#include "ActorContext.h"

BaseSceneViewer::BaseSceneViewer(InputSystem* inputSystem, Graphics* graphics)
    : inputSystem(inputSystem), graphics(graphics)
{
    deltaTimeHandler = new DeltaTimeHandler();
    //lightActor = new A_Light();
}

InputSystem* BaseSceneViewer::GetInputSystem() const
{
    return inputSystem;
}

Graphics* BaseSceneViewer::GetGraphics() const
{
    return graphics;
}

ActorContext BaseSceneViewer::GetActorContext() const
{
    return { graphics, inputSystem, deltaTimeHandler };
}

ACS_Light* BaseSceneViewer::GetLight()
{

}

void BaseSceneViewer::Update(const float engineDeltaTime)
{
    deltaTimeHandler->SetParentDeltaTime(engineDeltaTime);
}
