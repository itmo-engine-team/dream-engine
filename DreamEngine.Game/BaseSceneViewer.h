#pragma once

#include <vector>

#include "DeltaTimeHandler.h"
#include "ActorContext.h"
#include "ModelData.h"
#include "A_Light.h"
#include "A_Spectator.h"

class Graphics;
class InputSystem;

class BaseSceneViewer
{
public:

    BaseSceneViewer(InputSystem* inputSystem, Graphics* graphics);

    InputSystem* GetInputSystem() const;
    Graphics* GetGraphics() const;
    ActorContext* GetActorContext() const;

    virtual ACS_Camera* GetCamera() const;
    ACS_Light* GetLight() const;

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
    ActorContext* actorContext;

    virtual void createBaseSceneActors();

};

