#pragma once

#include "Graphics.h"
#include "InputSystem.h"
#include "AssetManager.h"

class GameAssetManager;
class DeltaTimeHandler;
class ACS_Light;
class ACS_Camera;
class NavMesh;

class ActorContext
{

public:

    ActorContext(Graphics* graphics,
        InputSystem* inputSystem,
        DeltaTimeHandler* deltaTimeHandler,
        AssetManager* assetManager,
        GameAssetManager* gameAssetManager
    ) : graphics(graphics),
        inputSystem(inputSystem),
        deltaTimeHandler(deltaTimeHandler),
        assetManager(assetManager),
        gameAssetManager(gameAssetManager)
    {}

    Graphics* GetGraphics() const;
    InputSystem* GetInputSystem() const;
    DeltaTimeHandler* GetDeltaTimeHandler() const;
    AssetManager* GetAssetManager() const;
    GameAssetManager* GetGameAssetManager() const;

    ACS_Light* GetLight() const;
    void SetLight(ACS_Light* lightComponent);

    ACS_Camera* GetCamera() const;
    void SetCamera(ACS_Camera* cameraComponent);

    NavMesh* GetNavMesh() const;
    void SetNavMesh(NavMesh* newNavMesh);

    bool IsGameMode() const;
    void SetGameMode(bool isGameMode);

private:

    Graphics* graphics;
    InputSystem* inputSystem;
    DeltaTimeHandler* deltaTimeHandler;
    AssetManager* assetManager;
    GameAssetManager* gameAssetManager;

    bool isGameMode = false;

    NavMesh* navMesh = nullptr;

    ACS_Light* light;
    ACS_Camera* camera;

};

