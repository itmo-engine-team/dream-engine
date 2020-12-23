#include "BaseSceneViewer.h"

#include "Graphics.h"
#include "MeshRenderer.h"

#include "Actor.h"
#include "A_Light.h"
#include "A_Spectator.h"
#include "ActorContext.h"
#include "ACS_StaticModel.h"

BaseSceneViewer::BaseSceneViewer(InputSystem* inputSystem, Graphics* graphics)
    : inputSystem(inputSystem), graphics(graphics)
{
    deltaTimeHandler = new DeltaTimeHandler();
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

ACS_Camera* BaseSceneViewer::GetCamera() const
{
    return spectatorActor->GetCameraComponent();
}

ACS_Light* BaseSceneViewer::GetLight() const
{
    return lightActor->GetLightComponent();
}

void BaseSceneViewer::Init()
{
    createBaseSceneActors();

    for (Actor* baseActor : baseSceneActors)
    {
        baseActor->Init();
    }
}

void BaseSceneViewer::Update(const float engineDeltaTime)
{
    deltaTimeHandler->SetParentDeltaTime(engineDeltaTime);

    for (Actor* baseActor : baseSceneActors)
    {
        baseActor->Update();
    }
}

void BaseSceneViewer::Render()
{
    for (Actor* baseActor : baseSceneActors)
    {
        baseActor->Draw();
    }
}

void BaseSceneViewer::RenderShadowMap()
{
    for (Actor* baseActor : baseSceneActors)
    {
        baseActor->DrawShadowMap();
    }
}

void BaseSceneViewer::createBaseSceneActors()
{
    const ActorContext context = GetActorContext();
    lightActor = new A_Light(context, new Transform({ -10, 10, -10 }));
    lightActor->GetTransform()->AddWorldRotation(Vector3::UnitX, 0.65f);
    lightActor->GetTransform()->AddWorldRotation(Vector3::UnitY, 0.75f);
    baseSceneActors.push_back(lightActor);

    spectatorActor = new A_Spectator(context, new Transform({ 0, 1, -6 }));
    baseSceneActors.push_back(spectatorActor);

    planeModel = MeshRenderer::CreateBoxModel({ 1, 1, 1, 1 }, { 3, 0.1, 3 });
    planeActor = new Actor(context, new Transform({ 0, 0, 0 }));
    planeActor->AddSceneComponent(new ACS_StaticModel(context, planeActor, new Transform({ 0, 0, 0 }), planeModel));
    baseSceneActors.push_back(planeActor);
}
