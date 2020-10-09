#pragma once

#include "GameObject/Component/CameraComponent.h"
#include "GameAssetManager/GameAssetManager.h"

class Engine;

class Game
{

public:

    Game(Engine* engine);

    Engine* GetEngine() const;

    GameAssetManager* GetGameAssetManager() const;
    virtual CameraComponent* GetCamera() const = 0;

    virtual void Update();
    virtual void Render();
    void SetGameDeltaTime(float deltaMultiplier);
    float GetWorldDeltaTime();

protected:

    Engine* engine;
    GameAssetManager* gameAssetManager;

    float gameDeltaTime;
    float gameDeltaTimeMultiplier;
    
    

};

