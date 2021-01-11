#include "Game.h"

#include "GameAssetManager.h"
#include "Scene.h"
#include "ACS_Collision.h"
#include "ACS_StaticModel.h"
#include "ACF_Movement.h"
#include "ACF_PlayerMovement.h"
#include "ACF_TargetReference.h"
#include "ACF_AI.h"
#include "MeshRenderer.h"
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
    navMesh->UpdateTransform(new TransformInfo({ 0, 0.11f, 0 }));

    playerModel = MeshRenderer::CreateBoxModel({ 1, 1, 0, 1 }, { 0.3f, 0.3f, 0.3f });
    playerActor = new Actor(actorContext);
    playerActor->UpdateTransform(new TransformInfo({ 0.5, 0, 0 }));
    playerActor->AddSceneComponent(new ACS_StaticModel(playerActor, playerModel));
    playerActor->AddSceneComponent(new ACS_Collision(playerActor, {0.3f, 0.3f}));
    playerActor->AddFixedComponent(new ACF_PlayerMovement(playerActor));
    playerActor->Init();

    model1 = MeshRenderer::CreateBoxModel({ 1, 1, 1, 1 }, { 0.3f, 0.3f, 0.8f });
    actor1 = new Actor(actorContext);
    actor1->UpdateTransform(new TransformInfo({ -1.65f, 0, 0 }));
    actor1->AddSceneComponent(new ACS_StaticModel(actor1, model1));
    actor1->AddSceneComponent(new ACS_Collision(actor1, { 0.3f, 0.8f }));
    actor1->Init();

    model2 = MeshRenderer::CreateBoxModel({ 1, 1, 1, 1 }, { 0.5f, 0.3f, 0.5f });
    actor2 = new Actor(actorContext);
    actor2->UpdateTransform(new TransformInfo({ 1.5f, 0, 0 }));
    actor2->AddSceneComponent(new ACS_StaticModel(actor2, model2));
    actor2->AddSceneComponent(new ACS_Collision(actor2, { 0.5f, 0.5f }));
    actor2->Init();

    followerModel = MeshRenderer::CreateBoxModel({ 0, 1, 1, 1 }, { 0.3f, 0.3f, 0.3f });
    followerActor = new Actor(actorContext);
    followerActor->UpdateTransform(new TransformInfo({ -2, 0, 0 }));
    followerActor->AddSceneComponent(new ACS_StaticModel(followerActor, followerModel));
    followerActor->AddSceneComponent(new ACS_Collision(followerActor, { 0.3f, 0.3f }));
    followerActor->AddFixedComponent(new ACF_TargetReference(followerActor, playerActor));
    followerActor->AddFixedComponent(new ACF_AI(followerActor));

    ACF_Movement* followerMovementComponent = new ACF_Movement(followerActor);
    followerActor->AddFixedComponent(followerMovementComponent);
    followerMovementComponent->SetSpeed(0.6f);

    followerActor->Init();
}

void Game::Update(const float engineDeltaTime)
{
    BaseSceneViewer::Update(engineDeltaTime);

    navMesh->GetNavMesh()->ResetPolygons();

    navMesh->GetNavMesh()->UpdatePolygons(actor1, actor1->GetTransform()->GetWorldPosition(), actor1->FindComponent<ACS_Collision>()->GetSize());
    navMesh->GetNavMesh()->UpdatePolygons(actor2, actor2->GetTransform()->GetWorldPosition(), actor2->FindComponent<ACS_Collision>()->GetSize());
    navMesh->GetNavMesh()->UpdatePolygons(playerActor, playerActor->GetTransform()->GetWorldPosition(), playerActor->FindComponent<ACS_Collision>()->GetSize());
    navMesh->GetNavMesh()->UpdatePolygons(followerActor, followerActor->GetTransform()->GetWorldPosition(), followerActor->FindComponent<ACS_Collision>()->GetSize());

    //followerActor->FindComponent<ACF_Movement>()->MoveTo(playerActor->GetTransform()->GetWorldPosition());

    actor1->Update();
    actor2->Update();
    playerActor->Update();
    followerActor->Update();

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

    actor1->Draw();
    actor2->Draw();
    playerActor->Draw();
    followerActor->Draw();

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