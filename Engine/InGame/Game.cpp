#include "Game.h"

#include "Engine.h"

Game::Game(Engine* engine) : engine(engine), gameAssetManager(engine->GetGameAssetManager())
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

void Game::SetGameDeltaTimeMultiplier(float deltaTimeMultiplier)
{
    gameDeltaTimeMultiplier = deltaTimeMultiplier;
}

float Game::GetGameDeltaTime()
{
    gameDeltaTime = engine->GetDeltaTime() * gameDeltaTimeMultiplier;
    return gameDeltaTime;
}
