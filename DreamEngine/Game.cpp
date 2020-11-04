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
        actor->RenderDeferred();
    }
}

void Game::RenderShadowMap() 
{
    
    for (auto actor : gameAssetManager->GetActors())
    {
        actor->DrawShadowMap();
    }
}

void Game::PrepareDeferredBuffer()
{
    // Set the render buffers to be the render target.
    deferredBuffers->SetRenderTargets(engine->GetGraphics()->GetContext());

    // Clear the render buffers.
    deferredBuffers->ClearRenderTargets(engine->GetGraphics()->GetContext(), 0.0f, 0.0f, 0.0f, 1.0f);
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