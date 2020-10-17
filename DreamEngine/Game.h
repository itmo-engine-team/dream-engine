#pragma once

#include "CameraComponent.h"
#include "GameAssetManager.h"

class Engine;

class Game
{

public:

    Game();

    Engine* GetEngine() const;

    GameAssetManager* GetGameAssetManager() const;
    virtual CameraComponent* GetCamera() const = 0;

    virtual void Init(Engine* engine);
    virtual void Update();
    virtual void Render();

    void SetGameDeltaTimeMultiplier(float deltaTimeMultiplier);
    float GetGameDeltaTimeMultiplier();
    float GetGameDeltaTime();

protected:

    Engine* engine;
    GameAssetManager* gameAssetManager;

    float gameDeltaTime;
    float gameDeltaTimeMultiplier = 1;
    
};

