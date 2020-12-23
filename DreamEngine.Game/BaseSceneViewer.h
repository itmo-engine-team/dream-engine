#pragma once

#include "DeltaTimeHandler.h"
#include <vector>

class SceneAssetInfo;
class Actor;
class A_Light;
class A_Spectator;
class ACS_Camera;
class ACS_Light;
class InputSystem;
class Graphics;
class ModelData;
struct ActorContext;

class BaseSceneViewer
{
public:

    BaseSceneViewer(InputSystem* inputSystem, Graphics* graphics);

    InputSystem* GetInputSystem() const;
    Graphics* GetGraphics() const;
    ActorContext GetActorContext() const;

    virtual ACS_Camera* GetCamera() const;
    virtual ACS_Light* GetLight() const;

    virtual void Init();
    virtual void Update(float engineDeltaTime);
    virtual void Render();
    virtual void RenderShadowMap();

protected:

    InputSystem* inputSystem;
    Graphics* graphics;
    DeltaTimeHandler* deltaTimeHandler;
    
    ModelData* planeModel;

    A_Light* lightActor;
    A_Spectator* spectatorActor;
    Actor* planeActor;

    std::vector<Actor*> baseSceneActors;

    virtual void createBaseSceneActors();

};

