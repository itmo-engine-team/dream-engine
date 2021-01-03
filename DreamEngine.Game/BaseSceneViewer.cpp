#include "BaseSceneViewer.h"

#include "Graphics.h"
#include "MeshRenderer.h"

#include "ACS_StaticModel.h"
#include "EngineConfigInfo.h"

BaseSceneViewer::BaseSceneViewer(EngineConfigInfo* engineConfigInfo, InputSystem* inputSystem, Graphics* graphics)
    : engineConfigInfo(engineConfigInfo), inputSystem(inputSystem), graphics(graphics)
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

ActorContext* BaseSceneViewer::GetActorContext() const
{
    return actorContext;
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
    actorContext = new ActorContext(graphics, inputSystem, deltaTimeHandler);

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
    lightActor = new A_Light(actorContext, new Transform({ -10, 10, -10 }));
    lightActor->GetTransform()->AddWorldRotation(Vector3::UnitX, 0.65f);
    lightActor->GetTransform()->AddWorldRotation(Vector3::UnitY, 0.75f);
    baseSceneActors.push_back(lightActor);
    actorContext->SetLight(lightActor->GetLightComponent());

    spectatorActor = new A_Spectator(actorContext, new Transform({ 0, 1, -6 }));
    baseSceneActors.push_back(spectatorActor);
    actorContext->SetCamera(spectatorActor->GetCameraComponent());

    planeModel = MeshRenderer::CreateBoxModel({ 1, 1, 1, 1 }, { 3, 0.1, 3 });
    planeActor = new Actor(actorContext, new Transform({ 0, 0, 0 }));
    planeActor->AddSceneComponent(new ACS_StaticModel(actorContext, planeActor, new Transform({ 0, 0, 0 }), planeModel));
    baseSceneActors.push_back(planeActor);
}
