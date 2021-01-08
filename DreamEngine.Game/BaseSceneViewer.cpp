#include "BaseSceneViewer.h"

#include "Graphics.h"
#include "MeshRenderer.h"

#include "A_Light.h"
#include "A_Spectator.h"
#include "ACS_StaticModel.h"
#include "EngineConfigInfo.h"
#include "ConstantBuffer.h"
#include "LightBuffer.h"
#include "DeltaTimeHandler.h"
#include "Transform.h"

BaseSceneViewer::BaseSceneViewer(EngineConfigInfo* engineConfigInfo,
    InputSystem* inputSystem, Graphics* graphics, AssetManager* assetManager)
    : engineConfigInfo(engineConfigInfo),
      inputSystem(inputSystem), graphics(graphics), assetManager(assetManager)
{
    deltaTimeHandler = new DeltaTimeHandler();

    sceneRenderer = new SceneRenderer(graphics);
}

void BaseSceneViewer::SetActive(const bool isActive)
{
    this->isActive = isActive;
}

SceneRenderer* BaseSceneViewer::GetSceneRenderer() const
{
    return sceneRenderer;
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
    actorContext = new ActorContext(graphics, inputSystem, deltaTimeHandler, assetManager);

    createBaseSceneActors();

    for (Actor* baseActor : baseSceneActors)
    {
        baseActor->Init();
    }
}

void BaseSceneViewer::Update(const float engineDeltaTime)
{
    if (!isActive) return;

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

void BaseSceneViewer::RenderPipeline()
{
    // Deferred renders to textures
    graphics->GetAnnotation()->BeginEvent(L"Deferred");
    sceneRenderer->PrepareDeferredBuffer();
    Render();
    graphics->GetAnnotation()->EndEvent();

    // Render shadow map
    graphics->GetAnnotation()->BeginEvent(L"ShadowMap");
    sceneRenderer->PrepareRenderShadowMap();
    RenderShadowMap();
    graphics->GetAnnotation()->EndEvent();

    // Prepare to render
    graphics->GetAnnotation()->BeginEvent(L"Scene");
    if (engineConfigInfo->IsGameMode())
    {
        graphics->PrepareRenderBackBuffer();
    }
    else
    {
        sceneRenderer->PrepareRenderSceneMap();
    }
    sceneRenderer->PrepareRenderScene();

    const ConstantBuffer cb =
    {
        Matrix::Identity,
        Matrix::Identity,
        Matrix::Identity,
        GetLight()->GetViewMatrix(),
        GetLight()->GetProjectionMatrix(),
    };

    const LightBuffer lb =
    {
        Vector4{0.15f, 0.15f, 0.15f, 1.0f},
        Vector4{1.0f, 1.0f, 1.0f, 1.0f},
        GetLight()->GetDirection(),
        100.0f,
        {1.0f, 1.0f, 1.0f, 1.0f }
    };

    sceneRenderer->RenderScene(cb, lb);
    graphics->GetAnnotation()->EndEvent();
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
    planeActor->AddSceneComponent(new ACS_StaticModel(planeActor, new Transform({ 0, 0, 0 }), planeModel));
    baseSceneActors.push_back(planeActor);
}
