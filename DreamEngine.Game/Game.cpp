#include "Game.h"

#include "GameAssetManager.h"
#include "Scene.h"
#include "NavMesh.h"
#include "A_NavMesh.h"

Game::Game(EngineConfigInfo* engineConfigInfo,
    InputSystem* inputSystem, Graphics* graphics, AssetManager* assetManager)
    : BaseSceneViewer(engineConfigInfo, inputSystem, graphics, assetManager)
{
}

GameAssetManager* Game::GetGameAssetManager() const
{
    return gameAssetManager;
}

void Game::Init()
{
    BaseSceneViewer::Init();

    navMesh = new A_NavMesh(actorContext);
    navMesh->UpdateTransform(new TransformInfo({ 0, 0.11, 0 }));
}

void Game::Update(const float engineDeltaTime)
{
    BaseSceneViewer::Update(engineDeltaTime);

    navMesh->Update();

    if (currentScene != nullptr && currentScene->GetCurrentRoom() != nullptr)
    {
        for (Actor* actor : currentScene->GetCurrentRoom()->GetActors())
        {
            actor->Update();
        }
    }
}

void Game::Render()
{
    BaseSceneViewer::Render();

    navMesh->Draw();

    if (currentScene != nullptr && currentScene->GetCurrentRoom() != nullptr)
    {
        for (Actor* actor : currentScene->GetCurrentRoom()->GetActors())
        {
            actor->Draw();
        }
    }
}

void Game::RenderShadowMap() 
{
    BaseSceneViewer::RenderShadowMap();

    if (currentScene != nullptr && currentScene->GetCurrentRoom() != nullptr)
    {
        for (Actor* actor : currentScene->GetCurrentRoom()->GetActors())
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
    }

    currentScene = new Scene(GetActorContext(), sceneInfo);
}

Scene* Game::GetCurrentScene() const
{
    return currentScene;
}