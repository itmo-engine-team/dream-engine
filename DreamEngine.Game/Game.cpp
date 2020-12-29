#include "Game.h"

#include "GameAssetManager.h"
#include "Scene.h"
#include "ACS_Collision.h"
#include "ACS_StaticModel.h"
#include "MeshRenderer.h"
#include "NavMesh.h"

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
    BaseSceneViewer::Init();

    navMesh = new A_NavMesh(actorContext, new Transform({ 0, 0.11, 0 }));

    testModel = MeshRenderer::CreateBoxModel({ 1, 1, 1, 1 }, { 1, 0.5f, 1 });
    testBox = new Actor(actorContext, new Transform({ 0, 0, 0 }));
    testBox->AddSceneComponent(new ACS_StaticModel(actorContext, testBox, new Transform({ 0, 0, 0 }), testModel));
    testBox->AddSceneComponent(new ACS_Collision(actorContext, testBox, new Transform({ 0, 0, 0 }), Vector2{1.5f, 1.5f }));
}

void Game::Update(const float engineDeltaTime)
{
    BaseSceneViewer::Update(engineDeltaTime);

    testBox->Update();

    ACS_Collision* collision = testBox->FindComponent<ACS_Collision>();
    navMesh->GetNavMesh()->UpdatePolygons(collision->GetTransform()->GetWorldPosition(), collision->GetSize());

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

    testBox->Draw();

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