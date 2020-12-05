#include "PongGame.h"

#include <iostream>

#include "ErrorLogger.h"
#include "SimpleMath.h"

#include "Graphics.h"
#include "Texture.h"

using namespace DirectX::SimpleMath;

PongGame::PongGame() : Game()
{
    
}

PongGame::~PongGame()
{
    delete spectatorActor;
    spectatorActor = nullptr;

    delete ball;
    ball = nullptr;

    delete wall2;
    wall2 = nullptr;

    delete wall1;
    wall1 = nullptr;

    delete plane;
    plane = nullptr;

    delete ballModel;
    ballModel = nullptr;

    delete wallModel;
    wallModel = nullptr;

    delete plane;
    plane = nullptr;
}

void PongGame::Init(Engine* engine)
{
    Game::Init(engine);

    // Init Shaders

    texture = new Texture(engine->GetGraphics(), L"Meshes/eyeball/eyes_blue.jpg");
    gameAssetManager->AddTexture(texture);

    // Init Meshes

    planeModel = MeshRenderer::CreateBoxModel({ 0, 0.8, 0.8, 1 }, { 3.5f, 0.1f, 2 });
    wallModel = MeshRenderer::CreateBoxModel({ 0.8f, 0.8f, 0.8f, 0.5f }, { 3.5f, 0.1f, 0.1f });
    playerModel = MeshRenderer::CreateBoxModel({ 1, 1, 1, 1 }, { 0.1f, 0.1f, 0.5f });
    ballModel = new ModelData(engine->GetMeshRenderer(),
        "Meshes/eyeball/eyeball-mod.obj", texture);

    gameAssetManager->AddModel(planeModel);
    gameAssetManager->AddModel(wallModel);
    gameAssetManager->AddModel(playerModel);
    gameAssetManager->AddModel(ballModel);

    // Init objects

    plane = new Actor(this, new Transform({ 0, 0, 0 }));
    plane->AddComponent(new StaticModelComponent(this, plane, new Transform({ 0, 0, 0 }), planeModel));
    gameAssetManager->AddActor(plane);

    wall1 = new Actor(this, new Transform({ 0, 0.2f, 1.9f }));
    wall1->AddComponent(new StaticModelComponent(this, wall1, new Transform({ 0, 0, 0 }), wallModel));
    gameAssetManager->AddActor(wall1);

    wall2 = new Actor(this, new Transform({ 0, 0.2f, -1.9f }));
    wall2->AddComponent(new StaticModelComponent(this, wall2, new Transform({ 0, 0, 0 }), wallModel));
    gameAssetManager->AddActor(wall2);

   /* box3 = new Actor(this, new Transform({ 1, 1, 0 }));
    box3->AddComponent(new StaticModelComponent(this, box3, new Transform({ 0, 0, 0 }), wallModel));
    gameAssetManager->AddActor(box3);*/

    // Init ball
    ball = new Ball(this, new Transform({ 0, 0.8f, 0 }));
    ballSphere = new StaticModelComponent(this, ball, new Transform({ 0, 0, 0 }), ballModel);
    ball->AddComponent(ballSphere);
    gameAssetManager->AddActor(ball);

    ball->SpeedX = ball->SPEED / GetEngine()->GetGraphics()->GetWindow()->GetScreenWidth();
    ball->SpeedZ = ball->SPEED / GetEngine()->GetGraphics()->GetWindow()->GetScreenHeight();

    //Create Players
    player1 = new Player(this, new Transform({ 2.9f, 0.8f, 0 }));
    player1->AddComponent(new StaticModelComponent(this, player1, new Transform({ 0, 0, 0 }), playerModel));
    gameAssetManager->AddActor(player1);

    player2 = new Player(this, new Transform({ -2.9f, 0.8f, 0 }));
    player2->AddComponent(new StaticModelComponent(this, player2, new Transform({ 0, 0, 0 }), playerModel));
    gameAssetManager->AddActor(player2);

    spectatorActor = new SpectatorActor(this, new Transform({ 0, 10, 0 }));
    gameAssetManager->AddActor(spectatorActor);
    spectatorActor->GetTransform()->AddWorldRotation(Vector3::UnitX, 1.57f);

    lightActor = new LightActor(this, new Transform({ -10, 10, -10 }));
    lightActor->AddComponent(new StaticModelComponent(this, lightActor, new Transform({ 0, 0, 0 }), wallModel));
    lightActor->AddComponent(new StaticModelComponent(this, lightActor, new Transform({ 0, 0, 0.5 }),
        MeshRenderer::CreateBoxModel({ 1, 1, 1, 1 }, { 0.03f, 0.03f, 0.5 })));

    lightActor->GetTransform()->AddWorldRotation(Vector3::UnitX, 0.65f);
    lightActor->GetTransform()->AddWorldRotation(Vector3::UnitY, 0.75f);
}

CameraComponent* PongGame::GetCamera() const
{
    return spectatorActor->GetCameraComponent();
}

LightComponent* PongGame::GetLight() const
{
    return lightActor->GetLightComponent();
}

void PongGame::Update()
{
    Game::Update();

    // Skip if camera moves
    if (engine->GetInputSystem()->IsMouseButtonPressed(MouseInput::Right)) return; 

    // Update sphere movement
    if (engine->GetInputSystem()->IsKeyPressed(KeyboardInput::Key_W))
    {
        if (player1->GetTransform()->GetWorldPosition().z > 1.24f) return;

        player1->GetTransform()->AddWorldPosition({ 0.0f, 0.0f, engine->GetDeltaTime() * 1.5f });
    }
    if (engine->GetInputSystem()->IsKeyPressed(KeyboardInput::Key_S))
    {
        if (player1->GetTransform()->GetWorldPosition().z < -1.24f) return;

        player1->GetTransform()->AddWorldPosition({ 0.0f, 0.0f, -engine->GetDeltaTime() * 1.5f });
    }
    if (engine->GetInputSystem()->IsKeyPressed(KeyboardInput::Arrow_Up))
    {
        if (player2->GetTransform()->GetWorldPosition().z > 1.24f) return;

        player2->GetTransform()->AddWorldPosition({ 0.0f, 0.0f, engine->GetDeltaTime() * 1.5f });
    }
    if (engine->GetInputSystem()->IsKeyPressed(KeyboardInput::Arrow_Down))
    {
        if (player2->GetTransform()->GetWorldPosition().z < -1.24f) return;

        player2->GetTransform()->AddWorldPosition({ 0.0f, 0.0f, -engine->GetDeltaTime() * 1.5f });
        //playerSphere->GetTransform()->AddRelativeRotation({ 0, 0, 1 }, engine->GetDeltaTime());
    }

    /*collisionCheck(box1);
    collisionCheck(box2);
    collisionCheck(box3);*/
}

void PongGame::Render()
{
    Game::Render();
    lightActor->Draw();
}

void PongGame::collisionCheck(GameObject* gameObject)
{
    /*if (!gameObject->Transform->HasParent() && katamariSphere->collider->Contains(gameObject->Transform->GetWorldPosition()))
    {
        gameObject->Transform->SetParent(katamariSphere->Transform);
    }*/
}
