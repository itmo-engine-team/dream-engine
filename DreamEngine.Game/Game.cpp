#include "Game.h"

#include "GameAssetManager.h"
#include "Scene.h"
#include "ACS_Collision.h"
#include "NavMesh.h"

Game::Game(EngineConfigInfo* engineConfigInfo, InputSystem* inputSystem, Graphics* graphics)
    : BaseSceneViewer(engineConfigInfo, inputSystem, graphics)
{
    gameAssetManager = new GameAssetManager();
}

GameAssetManager* Game::GetGameAssetManager() const
{
    return gameAssetManager;
}

void Game::Init()
{
    BaseSceneViewer::Init();

    navMesh = new A_NavMesh(actorContext, new Transform({ 0, 0.11, 0 }));  
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