#pragma once

#include "DeltaTimeHandler.h"

class SceneAssetInfo;
class ACS_Camera;
class A_Light;
class ACS_Light;
class InputSystem;
class Graphics;
struct ActorContext;

class BaseSceneViewer
{
public:

    BaseSceneViewer(InputSystem* inputSystem, Graphics* graphics);

    InputSystem* GetInputSystem() const;
    Graphics* GetGraphics() const;
    ActorContext GetActorContext() const;

    virtual ACS_Camera* GetCamera() const = 0;
    virtual ACS_Light* GetLight();

    virtual void Init() = 0;
    virtual void Update(float engineDeltaTime);
    virtual void Render() = 0;
    virtual void RenderShadowMap() = 0;

protected:

    InputSystem* inputSystem;
    Graphics* graphics;
    DeltaTimeHandler* deltaTimeHandler;

    A_Light* lightActor;

};

