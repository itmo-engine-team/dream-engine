#include "KatamariGame.h"

#include "SimpleMath.h"

using namespace DirectX::SimpleMath;

KatamariGame::KatamariGame()
{
    
}

KatamariGame::~KatamariGame()
{
    /*delete spectatorActor;
    spectatorActor = nullptr;

    delete katamariPlayer;
    katamariPlayer = nullptr;

    delete box3;
    box3 = nullptr;

    delete box2;
    box2 = nullptr;

    delete box1;
    box1 = nullptr;

    delete plane;
    plane = nullptr;

    delete playerModel;
    playerModel = nullptr;

    delete boxModel;
    boxModel = nullptr;

    delete plane;
    plane = nullptr;*/
}

/*void KatamariGame::Init(InputSystem* inputSystem, Graphics* graphics)
{
    Game::Init(inputSystem, graphics);

    // Init Shaders

    texture = new Texture(graphics, L"Meshes/eyeball/eyes_blue.jpg");
    gameAssetManager->AddTexture(texture);

    // Init Meshes

    planeModel = MeshRenderer::CreateBoxModel({ 1, 1, 1, 1 }, { 3, 0.1, 3 });
    boxModel = MeshRenderer::CreateBoxModel({ 1, 1, 1, 1 }, { 0.1, 0.1, 0.1 });

    playerModel = new ModelData(graphics->GetMeshRenderer(),
        "Meshes/eyeball/eyeball-mod.obj", texture);

    gameAssetManager->AddModel(planeModel);
    gameAssetManager->AddModel(boxModel);
    gameAssetManager->AddModel(playerModel);

    // Init objects

    plane = new Actor(this, new Transform({ 0, 0, 0 }));
    plane->AddSceneComponent(new ACS_StaticModel(this, plane, new Transform({ 0, 0, 0 }), planeModel));
    gameAssetManager->AddActor(plane);

    box1 = new Actor(this, new Transform({ -1, 1, 0 }));
    box1->AddSceneComponent(new ACS_StaticModel(this, box1, new Transform({ 0, 0, 0 }), boxModel));
    gameAssetManager->AddActor(box1);

    box2 = new Actor(this, new Transform({ -0.5, 1, -1 }));
    box2->AddSceneComponent(new ACS_StaticModel(this, box2, new Transform({ 0, 0, 0 }), boxModel));
    gameAssetManager->AddActor(box2);

    box3 = new Actor(this, new Transform({ 1, 1, 0 }));
    box3->AddSceneComponent(new ACS_StaticModel(this, box3, new Transform({ 0, 0, 0 }), boxModel));
    gameAssetManager->AddActor(box3);

    katamariPlayer = new KatamariSphere(this, new Transform({ 0, 0.8, 0 }));
    playerSphere = new ACS_StaticModel(this, katamariPlayer, new Transform({ 0, 0, 0 }), playerModel);
    katamariPlayer->AddSceneComponent(playerSphere);
    gameAssetManager->AddActor(katamariPlayer);

    spectatorActor = new A_Spectator(this, new Transform({ 0, 1, -6 }));
    gameAssetManager->AddActor(spectatorActor);

    lightActor = new A_Light(this, new Transform({ -10, 10, -10 }));
    lightActor->AddSceneComponent(new ACS_StaticModel(this, lightActor, new Transform({ 0, 0, 0 }), boxModel));
    lightActor->AddSceneComponent(new ACS_StaticModel(this, lightActor, new Transform({ 0, 0, 0.5 }),
        MeshRenderer::CreateBoxModel({ 1, 1, 1, 1 }, { 0.03, 0.03, 0.5 })));

    lightActor->GetTransform()->AddWorldRotation(Vector3::UnitX, 0.65f);
    lightActor->GetTransform()->AddWorldRotation(Vector3::UnitY, 0.75f);
}

ACS_Camera* KatamariGame::GetCamera() const
{
    return spectatorActor->GetCameraComponent();
}

ACS_Light* KatamariGame::GetLight() const
{
    return lightActor->GetLightComponent();
}

void KatamariGame::Update(float engineDeltaTime)
{
    Game::Update(engineDeltaTime);

    // Skip if camera moves
    if (inputSystem->IsMouseButtonPressed(MouseInput::Right)) return; 

    // Update sphere movement
    if (inputSystem->IsKeyPressed(KeyboardInput::Key_W))
    {
        katamariPlayer->GetTransform()->AddWorldPosition({ 0.0f, 0.0f, GetGameDeltaTime() });
        playerSphere->GetTransform()->AddRelativeRotation({ 1, 0, 0 }, GetGameDeltaTime());
    }
    if (inputSystem->IsKeyPressed(KeyboardInput::Key_A))
    {
        katamariPlayer->GetTransform()->AddWorldPosition({ GetGameDeltaTime(), 0.0f, 0.0f });
        playerSphere->GetTransform()->AddRelativeRotation({ 0, 0, 1 }, -GetGameDeltaTime());
    }
    if (inputSystem->IsKeyPressed(KeyboardInput::Key_S))
    {
        katamariPlayer->GetTransform()->AddWorldPosition({ 0.0f, 0.0f, -GetGameDeltaTime() });
        playerSphere->GetTransform()->AddRelativeRotation({ 1, 0, 0 }, -GetGameDeltaTime());
    }
    if (inputSystem->IsKeyPressed(KeyboardInput::Key_D))
    {
        katamariPlayer->GetTransform()->AddWorldPosition({ -GetGameDeltaTime(), 0.0f, 0.0f });
        playerSphere->GetTransform()->AddRelativeRotation({ 0, 0, 1 }, GetGameDeltaTime());
    }

    collisionCheck(box1);
    collisionCheck(box2);
    collisionCheck(box3);
}

void KatamariGame::Render()
{
    Game::Render();
    lightActor->Draw();
}
*/
