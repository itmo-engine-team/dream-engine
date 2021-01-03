#pragma once

#include "BaseSceneViewer.h"
#include "A_NavMesh.h"

class Scene;
class SceneAssetInfo;
class GameAssetManager;

class Game : public BaseSceneViewer
{

public:

    Game(InputSystem* inputSystem, Graphics* graphics);

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