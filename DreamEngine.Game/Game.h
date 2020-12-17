#pragma once

#include "CameraComponent.h"
#include "LightComponent.h"
#include "InputSystem.h"

class Graphics;
class GameAssetManager;

class Game
{

public:

    Game();

    InputSystem* GetInputSystem() const;
    Graphics* GetGraphics() const;
    GameAssetManager* GetGameAssetManager() const;
    virtual CameraComponent* GetCamera() const = 0;
    virtual LightComponent* GetLight() const = 0;

    virtual void Init(InputSystem* inputSystem, Graphics* graphics);
    virtual void Update(float engineDeltaTime);
    virtual void Render();
    void RenderShadowMap();

    void SetGameDeltaTimeMultiplier(float deltaTimeMultiplier);
    float GetGameDeltaTimeMultiplier();
    float GetGameDeltaTime();

protected:

    InputSystem* inputSystem;
    Graphics* graphics;

    GameAssetManager* gameAssetManager;

    float engineDeltaTime;
    float gameDeltaTimeMultiplier = 1;

};

