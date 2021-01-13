#include "Game.h"

#include "GameAssetManager.h"
#include "Scene.h"
#include "NavMesh.h"
#include "A_NavMesh.h"
#include "EngineConfigInfo.h"
#include "SceneAssetInfo.h"
#include "ErrorLogger.h"
#include "DeltaTimeHandler.h"

Game::Game(EngineConfigInfo* engineConfigInfo,
           InputSystem* inputSystem, Graphics* graphics, AssetManager* assetManager)
    : BaseSceneViewer(engineConfigInfo, inputSystem, graphics, assetManager)
{
}

bool Game::IsGameOver() const
{
    return isGameOver;
}

GameAssetManager* Game::GetGameAssetManager() const
{
    return gameAssetManager;
}

void Game::Init()
{
    BaseSceneViewer::Init();

    actorContext->SetGameMode(engineConfigInfo->IsGameMode());

    navMesh = new A_NavMesh(actorContext);
    navMesh->UpdateTransform(new TransformInfo({ 0, 0.11, 0 }));

    if (!actorContext->IsGameMode()) return;

    // Init scene if is game mode
    auto sceneAsset = dynamic_cast<SceneAssetInfo*>(assetManager->GetAssetByType(
        AssetType::Scene, engineConfigInfo->GetStartSceneId()));

    if (sceneAsset == nullptr)
    {
        ErrorLogger::Log(Error, "Start scene is not existed");
    }

    LoadScene(sceneAsset);
    StartGame();
}

void Game::Update(const float engineDeltaTime)
{
    BaseSceneViewer::Update(engineDeltaTime);

    navMesh->Update();

    // Check game mode
    if (!actorContext->IsGameMode()) return;

    // Check game over
    if (isGameOver) return;

    if (!isGameOver && gameAssetManager->IsGameOver())
    {
        isGameOver = true;
        deltaTimeHandler->SetMultiplier(0);
    }

    // Update game objects on scene
    if (currentScene != nullptr)
    {
        for (Actor* actor : gameAssetManager->GetActors())
        {
            actor->Update();
        }
    }
}

void Game::Render()
{
    BaseSceneViewer::Render();

    navMesh->Draw();

    if (currentScene != nullptr /*&& currentScene->GetCurrentRoom() != nullptr*/)
    {
        for (Actor* actor : gameAssetManager->GetActors())
        {
            actor->Draw();
        }
    }
}

void Game::RenderShadowMap() 
{
    BaseSceneViewer::RenderShadowMap();

    if (currentScene != nullptr /*&& currentScene->GetCurrentRoom() != nullptr*/)
    {
        for (Actor* actor : gameAssetManager->GetActors())
        {
            actor->DrawShadowMap();
        }
    }
}

void Game::LoadScene(SceneAssetInfo* sceneInfo)
{
    if (currentScene != nullptr)
    {
        delete currentScene;
        currentScene = nullptr;
        gameAssetManager->Clear();
    }

    currentSceneInfo = sceneInfo;
    currentScene = new Scene(this, GetActorContext(), sceneInfo);
}

Scene* Game::GetCurrentScene() const
{
    return currentScene;
}

void Game::StartGame()
{
    actorContext->SetGameMode(true);
    currentScene->UpdateCameraTransform();

    for (auto actor : gameAssetManager->GetActors())
    {
        actor->Init();
    }
}

void Game::StopGame()
{
    actorContext->SetGameMode(false);

    LoadScene(currentSceneInfo);
}
