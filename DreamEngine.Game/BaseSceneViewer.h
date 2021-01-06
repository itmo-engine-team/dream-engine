#pragma once

#include <vector>

#include "ModelData.h"
#include "SceneRenderer.h"

class EngineConfigInfo;
class ActorContext;
class Graphics;
class InputSystem;
class ACS_Light;
class ACS_Camera;
class A_Spectator;
class A_Light;
class Actor;
class DeltaTimeHandler;

class BaseSceneViewer
{
public:

    BaseSceneViewer(EngineConfigInfo* engineConfigInfo, InputSystem* inputSystem, Graphics* graphics);

    void SetActive(bool isActive);

    SceneRenderer* GetSceneRenderer() const;
    InputSystem* GetInputSystem() const;
    Graphics* GetGraphics() const;
    ActorContext* GetActorContext() const;

    virtual ACS_Camera* GetCamera() const;
    ACS_Light* GetLight() const;

    virtual void Init();
    virtual void Update(float engineDeltaTime);
    virtual void Render();
    virtual void RenderShadowMap();

    void RenderPipeline();

protected:

    bool isActive = true;

    SceneRenderer* sceneRenderer;

    EngineConfigInfo* engineConfigInfo;
    InputSystem* inputSystem;
    Graphics* graphics;
    DeltaTimeHandler* deltaTimeHandler;
    
    ModelData* planeModel;

    A_Light* lightActor;
    A_Spectator* spectatorActor;
    Actor* planeActor;

    std::vector<Actor*> baseSceneActors;
    ActorContext* actorContext;

    virtual void createBaseSceneActors();

};

