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

void Game::SetGameDeltaTime(float deltaMultiplier)
{
    gameDeltaTimeMultiplier = deltaMultiplier;
}

float Game::GetWorldDeltaTime()
{
    gameDeltaTime = engine->GetDeltaTime() * gameDeltaTimeMultiplier;
    return gameDeltaTime;
}
