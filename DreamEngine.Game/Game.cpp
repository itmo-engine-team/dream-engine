#include "Game.h"

#include "GameAssetManager.h"
#include "Scene.h"

Game::Game()
{
    gameAssetManager = new GameAssetManager();
}

InputSystem* Game::GetInputSystem() const
{
    return inputSystem;
}

Graphics* Game::GetGraphics() const
{
    return graphics;
}

GameAssetManager* Game::GetGameAssetManager() const
{
    return gameAssetManager;
}

void Game::Init(InputSystem* inputSystem, Graphics* graphics)
{
    this->inputSystem = inputSystem;
    this->graphics = graphics;
}

void Game::Update(const float engineDeltaTime)
{
    this->engineDeltaTime = engineDeltaTime;

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

void Game::SetGameDeltaTimeMultiplier(float deltaTimeMultiplier)
{
    gameDeltaTimeMultiplier = std::clamp(deltaTimeMultiplier, 0.0f, 1.0f);
}

float Game::GetGameDeltaTimeMultiplier()
{
    return gameDeltaTimeMultiplier;
}

float Game::GetGameDeltaTime()
{
    return engineDeltaTime * gameDeltaTimeMultiplier;
}
