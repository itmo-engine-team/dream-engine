#pragma once

#include "BaseSceneViewer.h"

class Scene;
class SceneAssetInfo;
class GameAssetManager;
class A_NavMesh;

class Game : public BaseSceneViewer
{

public:

    Game(EngineConfigInfo* engineConfigInfo,
        InputSystem* inputSystem, Graphics* graphics, AssetManager* assetManager);

    GameAssetManager* GetGameAssetManager() const;

    void Init() override;
    void Update(float engineDeltaTime) override;
    void Render() override;
    void RenderShadowMap() override;

    void LoadScene(SceneAssetInfo* sceneInfo);
    Scene* GetCurrentScene() const;

protected:

    GameAssetManager* gameAssetManager;

    Scene* currentScene = nullptr;

    A_NavMesh* navMesh;
};