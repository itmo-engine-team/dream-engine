#include "Game.h"

#include "Engine.h"

Game::Game()
{

}

Engine* Game::GetEngine() const
{
    return engine;
}

GameAssetManager* Game::GetGameAssetManager() const
{
    return gameAssetManager;
}

void Game::Init(Engine* engine)
{
    this->engine = engine;
    this->gameAssetManager = engine->GetGameAssetManager();
}

void Game::Update()
{
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
    gameDeltaTime = engine->GetDeltaTime() * gameDeltaTimeMultiplier;
    return gameDeltaTime;
}

void Game::Render2D()
{

}
