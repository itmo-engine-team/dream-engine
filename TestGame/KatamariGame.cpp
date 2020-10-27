#include "KatamariGame.h"

#include <iostream>

#include "ErrorLogger.h"
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

    shadowMapTexture = new Texture(engine, engine->GetGraphics()->shadowMap);
    gameAssetManager->AddTexture(texture);

    texturedShader = new TexturedShader(engine->GetGraphics(), L"Shaders/ShaderTextured.fx", texture);
    texturedShader = new TexturedShader(engine->GetGraphics(), L"Shaders/ShaderDeferred.fx", texture);
    texturedShader->Init();
    gameAssetManager->AddShader(texturedShader);

    texturedShadowShader = new TexturedShader(engine->GetGraphics(), L"Shaders/ShaderModelOnlyTexture.fx", shadowMapTexture);
    texturedShadowShader->Init();
    gameAssetManager->AddShader(texturedShadowShader);

    shader = new Shader(engine->GetGraphics(), L"Shaders/Shader.fx");
    shader->Init();
    gameAssetManager->AddShader(shader);

    // Deferred
   
    // Create the light shader object.
    lightShader = new LightShader(engine->GetGraphics(), L"Shaders/Light.fx", texture);
    // Initialize the light shader object.
    lightShader->Initialize();
   

    // Init Meshes

    planeModel = MeshRenderer::CreateBoxModel(shader, { 1, 1, 1, 1 }, { 2, 0.1, 2 });
    boxModel = MeshRenderer::CreateBoxModel(shader, { 1, 1, 1, 1 }, { 0.1, 0.1, 0.1 });
    quardModel = MeshRenderer::CreateQuardModel(texturedShadowShader, { 1, 1, 1 });

    playerModel = new ModelData(engine->GetMeshRenderer(), 
        "Meshes/eyeball/eyeball-mod.obj", texturedShader);

    gameAssetManager->AddModel(planeModel);
    gameAssetManager->AddModel(boxModel);
    gameAssetManager->AddModel(playerModel);
    gameAssetManager->AddModel(quardModel);

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

    quard = new Actor(this, new Transform({ 1, 1, 0 }));
    quard->AddComponent(new StaticModelComponent(this, quard, new Transform({ 0, 0, 0 }), quardModel));

    katamariPlayer = new KatamariSphere(this, new Transform({ 0, 0.8, 0 }));
    playerSphere = new StaticModelComponent(this, katamariPlayer, new Transform({ 0, 0, 0 }), playerModel);
    katamariPlayer->AddComponent(playerSphere);
    gameAssetManager->AddActor(katamariPlayer);

    spectatorActor = new SpectatorActor(this, new Transform({ 0, 1, -6 }));
    gameAssetManager->AddActor(spectatorActor);

    lightActor = new LightActor(this, new Transform({ 0, 3, -6 }));
    //lightActor->GetTransform()->AddWorldRotation(Vector3::UnitX, 30);
    gameAssetManager->AddActor(lightActor);
}

CameraComponent* KatamariGame::GetCamera() const
{
    return spectatorActor->GetCameraComponent();
}

LightComponent* KatamariGame::GetLight() const
{
    return lightActor->GetLightComponent();
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

void KatamariGame::Render()
{
    Game::Render();
    quard->Draw();
}

void KatamariGame::collisionCheck(GameObject* gameObject)
{
    /*if (!gameObject->Transform->HasParent() && katamariSphere->collider->Contains(gameObject->Transform->GetWorldPosition()))
    {
        gameObject->Transform->SetParent(katamariSphere->Transform);
    }*/
}
