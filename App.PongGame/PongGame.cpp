#include "PongGame.h"

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

    planeModel = MeshRenderer::CreateBoxModel({ 0, 0.8, 0.8, 1 }, { 5.5f, 0.1f, 3.7f });
    wallModel = MeshRenderer::CreateBoxModel({ 0.8f, 0.8f, 0.8f, 0.5f }, { 5.5f, 0.5f, 0.1f });
    gateModel = MeshRenderer::CreateBoxModel({ 0.8f, 0.8f, 0.8f, 0.5f }, { 0.1f, 0.5f, 4.2f });
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

    // Wall
    wall1 = new Wall(this, new Transform({ 0, 0.2f, 3.6f }));
    wall1->AddComponent(new StaticModelComponent(this, wall1, new Transform({ 0, 0, 0 }), wallModel));
    gameAssetManager->AddActor(wall1);

    wall2 = new Wall(this, new Transform({ 0, 0.2f, -3.6f }));
    wall2->AddComponent(new StaticModelComponent(this, wall2, new Transform({ 0, 0, 0 }), wallModel));
    gameAssetManager->AddActor(wall2);

    // Gate
    gate1 = new Gate(this, new Transform({ -5.7f, 0, 0 }));
    gate1->AddComponent(new StaticModelComponent(this, gate1, new Transform({ 0, 0, 0 }), gateModel));
    gameAssetManager->AddActor(gate1);

    gate2 = new Gate(this, new Transform({ 5.7f, 0, 0 }));
    gate2->AddComponent(new StaticModelComponent(this, gate2, new Transform({ 0, 0, 0 }), gateModel));
    gameAssetManager->AddActor(gate2);

    // Init ball
    ball = new Ball(this, new Transform({ 0, 0.8, 0 }));
    ballSphere = new StaticModelComponent(this, ball, new Transform({ 0, 0, 0 }), ballModel);
    ball->AddComponent(ballSphere);
    gameAssetManager->AddActor(ball);
    resetBall();

    //Create Players
    player1 = new Player(this, new Transform({ 4.9f, 0.8f, 0 }));
    player1->AddComponent(new StaticModelComponent(this, player1, new Transform({ 0, 0, 0 }), playerModel));
    gameAssetManager->AddActor(player1);

    player2 = new Player(this, new Transform({ -4.9f, 0.8f, 0 }));
    player2->AddComponent(new StaticModelComponent(this, player2, new Transform({ 0, 0, 0 }), playerModel));
    gameAssetManager->AddActor(player2);

    spectatorActor = new SpectatorActor(this, new Transform({ 0, 17, 0 }));
    gameAssetManager->AddActor(spectatorActor);
    spectatorActor->GetTransform()->AddWorldRotation(Vector3::UnitX, 1.57f);

    lightActor = new LightActor(this, new Transform({ -15, 15, -15 }));
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

    collisionCheck();

    // Skip if camera moves
    if (engine->GetInputSystem()->IsMouseButtonPressed(MouseInput::Right)) return; 

    // Update player location
    if (engine->GetInputSystem()->IsKeyPressed(KeyboardInput::Key_W))
    {
        if (player1->GetTransform()->GetWorldPosition().z > 2.8f) return;

        player1->GetTransform()->AddWorldPosition({ 0.0f, 0.0f, engine->GetDeltaTime() * 5.5f });
    }
    if (engine->GetInputSystem()->IsKeyPressed(KeyboardInput::Key_S))
    {
        if (player1->GetTransform()->GetWorldPosition().z < -2.8f) return;

        player1->GetTransform()->AddWorldPosition({ 0.0f, 0.0f, -engine->GetDeltaTime() * 5.5f });
    }
    if (engine->GetInputSystem()->IsKeyPressed(KeyboardInput::Arrow_Up))
    {
        if (player2->GetTransform()->GetWorldPosition().z > 2.8f) return;

        player2->GetTransform()->AddWorldPosition({ 0.0f, 0.0f, engine->GetDeltaTime() * 5.5f });
    }
    if (engine->GetInputSystem()->IsKeyPressed(KeyboardInput::Arrow_Down))
    {
        if (player2->GetTransform()->GetWorldPosition().z < -2.8f) return;

        player2->GetTransform()->AddWorldPosition({ 0.0f, 0.0f, -engine->GetDeltaTime() * 5.5f });
        //playerSphere->GetTransform()->AddRelativeRotation({ 0, 0, 1 }, engine->GetDeltaTime());
    } 
}

void PongGame::Render()
{
    Game::Render();
    lightActor->Draw();   
}

void PongGame::Render2D()
{
    wchar_t pretext[200];
    swprintf(pretext, 200, L"Player 1: %d\nPlayer 2: %d", player1Score, player2Score);
    GetEngine()->GetGraphics()->DrawTextOnScene(400, 100, pretext);
}

void PongGame::collisionCheck()
{

    if (ball->collider->Contains(*gate1->collider))
    {
        player1Score++;
        resetBall();
        return;
    }

    if (ball->collider->Contains(*gate2->collider))
    {
        player2Score++;
        resetBall();
        return;
    }

    if (lastHittedActor != wall1 && ball->collider->Contains(*wall1->collider) )
    {
        lastHittedActor = wall1;
        ball->Direction->z = -ball->Direction->z;
    }

    if (lastHittedActor != wall2 && ball->collider->Contains(*wall2->collider))
    {
        lastHittedActor = wall2;
        ball->Direction->z = -ball->Direction->z;
    }

    if (lastHittedActor != player1 && ball->collider->Contains(*player1->collider))
    {
        lastHittedActor = player1;
        ball->Direction->z = -ball->Direction->z;
        ball->Direction->x = -ball->Direction->x;
    }

    if (lastHittedActor != player2 && ball->collider->Contains(*player2->collider))
    {
        lastHittedActor = player2;
        ball->Direction->z = -ball->Direction->z;
        ball->Direction->x = -ball->Direction->x;
    }
}

void PongGame::resetBall()
{
    lastHittedActor = nullptr;
    ball->GetTransform()->SetWorldPosition({ 0, ball->GetTransform()->GetWorldPosition().y, 0 });
    ball->SpeedX = ball->SPEED / GetEngine()->GetGraphics()->GetWindow()->GetScreenWidth();
    ball->SpeedZ = ball->SPEED / GetEngine()->GetGraphics()->GetWindow()->GetScreenHeight();
}
