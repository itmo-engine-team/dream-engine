#pragma once

#include "ACS_Camera.h"
#include "ACS_Light.h"
#include "InputSystem.h"

class SceneAssetInfo;
class Graphics;
class GameAssetManager;
class Scene;

class Game
{

public:

    Game();

    InputSystem* GetInputSystem() const;
    Graphics* GetGraphics() const;
    GameAssetManager* GetGameAssetManager() const;
    virtual ACS_Camera* GetCamera() const = 0;
    virtual ACS_Light* GetLight() const = 0;

    virtual void Init(InputSystem* inputSystem, Graphics* graphics);
    virtual void Update(float engineDeltaTime);
    virtual void Render();
    void RenderShadowMap();

    void LoadScene(SceneAssetInfo* sceneInfo);
    Scene* GetCurrentScene() const;

    void SetGameDeltaTimeMultiplier(float deltaTimeMultiplier);
    float GetGameDeltaTimeMultiplier();
    float GetGameDeltaTime();

protected:

    InputSystem* inputSystem;
    Graphics* graphics;

    GameAssetManager* gameAssetManager;

    Scene* currentScene;

    float engineDeltaTime;
    float gameDeltaTimeMultiplier = 1;

};

