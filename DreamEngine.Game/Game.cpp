#include "Game.h"

#include "GameAssetManager.h"

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

    for (auto actor : gameAssetManager->GetActors())
    {
        actor->Update();
    }
}

void Game::Render()
{
    for (auto actor : gameAssetManager->GetActors())
    {
        actor->Draw();
    }
}

void Game::RenderShadowMap() 
{
    
    for (auto actor : gameAssetManager->GetActors())
    {
        actor->DrawShadowMap();
    }
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
