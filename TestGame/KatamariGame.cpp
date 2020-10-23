#include "KatamariGame.h"

#include <iostream>
#include "SimpleMath.h"

#include "Texture.h"

using namespace DirectX::SimpleMath;

KatamariGame::KatamariGame() : Game()
{
    
}

KatamariGame::~KatamariGame()
{
    delete spectatorActor;
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
    plane = nullptr;
}

void KatamariGame::Init(Engine* engine)
{
    Game::Init(engine);

    // Init Shaders

    texture = new Texture(engine, L"Meshes/eyeball/eyes_blue.jpg");
    gameAssetManager->AddTexture(texture);

    texturedShader = new TexturedShader(engine, L"Shaders/ShaderTextured.fx", texture);
    texturedShader->Init();
    gameAssetManager->AddShader(texturedShader);

    shader = new Shader(engine, L"Shaders/Shader.fx");
    shader->Init();
    gameAssetManager->AddShader(shader);

    // Init Meshes

    planeModel = MeshRenderer::CreateBoxModel(shader, { 1, 1, 1, 1 }, { 2, 0.1, 2 });
    boxModel = MeshRenderer::CreateBoxModel(shader, { 1, 1, 1, 1 }, { 0.1, 0.1, 0.1 });
    playerModel = new ModelData(engine->GetMeshRenderer(), 
        "Meshes/eyeball/eyeball-mod.obj", texturedShader);

    gameAssetManager->AddModel(planeModel);
    gameAssetManager->AddModel(boxModel);
    gameAssetManager->AddModel(playerModel);

    // Init objects

    plane = new Actor(this, new Transform({ 0, 0, 0 }));
    plane->AddComponent(new StaticModelComponent(this, plane, new Transform({ 0, 0, 0 }), planeModel));
    gameAssetManager->AddActor(plane);

    box1 = new Actor(this, new Transform({ -1, 1, 0 }));
    box1->AddComponent(new StaticModelComponent(this, box1, new Transform({ 0, 0, 0 }), boxModel));
    gameAssetManager->AddActor(box1);

    box2 = new Actor(this, new Transform({ -0.5, 1, -1 }));
    box2->AddComponent(new StaticModelComponent(this, box2, new Transform({ 0, 0, 0 }), boxModel));
    gameAssetManager->AddActor(box2);

    box3 = new Actor(this, new Transform({ 1, 1, 0 }));
    box3->AddComponent(new StaticModelComponent(this, box3, new Transform({ 0, 0, 0 }), boxModel));
    gameAssetManager->AddActor(box3);

    katamariPlayer = new KatamariSphere(this, new Transform({ 0, 0.8, 0 }));
    playerSphere = new StaticModelComponent(this, katamariPlayer, new Transform({ 0, 0, 0 }), playerModel);
    katamariPlayer->AddComponent(playerSphere);
    gameAssetManager->AddActor(katamariPlayer);

    spectatorActor = new SpectatorActor(this, new Transform({ 0, 1, -6 }));
    gameAssetManager->AddActor(spectatorActor);
}

CameraComponent* KatamariGame::GetCamera() const
{
    return spectatorActor->GetCameraComponent();
}

void KatamariGame::Update()
{
    Game::Update();

    // Skip if camera moves
    if (engine->GetInputSystem()->IsMouseButtonPressed(MouseInput::Right)) return; 

    // Update sphere movement
    if (engine->GetInputSystem()->IsKeyPressed(KeyboardInput::Key_W))
    {
        katamariPlayer->GetTransform()->AddWorldPosition({ 0.0f, 0.0f, engine->GetDeltaTime() });
        playerSphere->GetTransform()->AddRelativeRotation({ 1, 0, 0 }, engine->GetDeltaTime());
    }
    if (engine->GetInputSystem()->IsKeyPressed(KeyboardInput::Key_A))
    {
        katamariPlayer->GetTransform()->AddWorldPosition({ engine->GetDeltaTime(), 0.0f, 0.0f });
        playerSphere->GetTransform()->AddRelativeRotation({ 0, 0, 1 }, -engine->GetDeltaTime());
    }
    if (engine->GetInputSystem()->IsKeyPressed(KeyboardInput::Key_S))
    {
        katamariPlayer->GetTransform()->AddWorldPosition({ 0.0f, 0.0f, -engine->GetDeltaTime() });
        playerSphere->GetTransform()->AddRelativeRotation({ 1, 0, 0 }, -engine->GetDeltaTime());
    }
    if (engine->GetInputSystem()->IsKeyPressed(KeyboardInput::Key_D))
    {
        katamariPlayer->GetTransform()->AddWorldPosition({ -engine->GetDeltaTime(), 0.0f, 0.0f });
        playerSphere->GetTransform()->AddRelativeRotation({ 0, 0, 1 }, engine->GetDeltaTime());
    }

    /*collisionCheck(box1);
    collisionCheck(box2);
    collisionCheck(box3);*/
}

void KatamariGame::collisionCheck(GameObject* gameObject)
{
    /*if (!gameObject->Transform->HasParent() && katamariSphere->collider->Contains(gameObject->Transform->GetWorldPosition()))
    {
        gameObject->Transform->SetParent(katamariSphere->Transform);
    }*/
}
