#include "Game.h"

#include "GameAssetManager.h"
#include "Scene.h"

Game::Game(InputSystem* inputSystem, Graphics* graphics) : BaseSceneViewer(inputSystem, graphics)
{
    gameAssetManager = new GameAssetManager();
}

GameAssetManager* Game::GetGameAssetManager() const
{
    return gameAssetManager;
}

void Game::Init()
{
}

void Game::Update(const float engineDeltaTime)
{
    BaseSceneViewer::Update(engineDeltaTime);

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

    currentScene = new Scene(this, sceneInfo);
}

Scene* Game::GetCurrentScene() const
{
    return currentScene;
}