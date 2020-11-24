#include "KatamariGame.h"

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

    texture = new Texture(engine, L"Meshes/eyeball/eyes_blue.jpg", L"Meshes/eyeball/eyes_blueN.jpg");
    gameAssetManager->AddTexture(texture);

    shadowMapTexture = new Texture(engine, engine->GetGraphics()->GetShadowMap());
    gameAssetManager->AddTexture(texture);

    texturedShader = new ModelShader(engine->GetGraphics(), L"Shaders/ShaderDeferred.fx", texture);
    texturedShader->Init();
    gameAssetManager->AddShader(texturedShader);

    shader = new ModelShader(engine->GetGraphics(), L"Shaders/ShaderDeferred.fx", nullptr);
    shader->Init();
    gameAssetManager->AddShader(shader);

    // Deferred
    bool result;

    // Create the light shader object.
    lightShader = new LightShader(engine->GetGraphics(), L"Shaders/ShaderDeferredLight.fx");
    lightShader->Init();
    gameAssetManager->AddShader(lightShader);

    deferredBuffers = new DeferredBuffers; 
    if (!deferredBuffers)
    {
        return;
    }

    // Initialize the deferred buffers object.
    result = deferredBuffers->Initialize(engine->GetGraphics()->GetDevice(), engine->GetScreenWidth(), engine->GetScreenHeight(), 100, 0.1f);
    if (!result)
    {
        ErrorLogger::Log(Error, "Error initializing DeferredBuffers");
        return;
    }

    // Init Meshes

    planeModel = MeshRenderer::CreateBoxModel(shader, { 1, 1, 1, 1 }, { 3, 0.1, 3 });
    boxModel = MeshRenderer::CreateBoxModel(shader, { 1, 1, 1, 1 }, { 0.1, 0.1, 0.1 });

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

    katamariPlayer = new KatamariSphere(this, new Transform({ 0, 0.8, 0 }));
    playerSphere = new StaticModelComponent(this, katamariPlayer, new Transform({ 0, 0, 0 }), playerModel);
    katamariPlayer->AddComponent(playerSphere);
    gameAssetManager->AddActor(katamariPlayer);

    spectatorActor = new SpectatorActor(this, new Transform({ 0, 1, -6 }));
    gameAssetManager->AddActor(spectatorActor);

    lightActor = new LightActor(this, new Transform({ -10, 10, -10 }));
    lightActor->AddComponent(new StaticModelComponent(this, lightActor, new Transform({ 0, 0, 0 }), boxModel));
    lightActor->AddComponent(new StaticModelComponent(this, lightActor, new Transform({ 0, 0, 0.5 }),
        MeshRenderer::CreateBoxModel(shader, { 1, 1, 1, 1 }, { 0.03, 0.03, 0.5 })));

    lightActor->GetTransform()->AddWorldRotation(Vector3::UnitX, 0.65f);
    lightActor->GetTransform()->AddWorldRotation(Vector3::UnitY, 0.75f);
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
    lightActor->Draw();
}

void KatamariGame::collisionCheck(GameObject* gameObject)
{
    /*if (!gameObject->Transform->HasParent() && katamariSphere->collider->Contains(gameObject->Transform->GetWorldPosition()))
    {
        gameObject->Transform->SetParent(katamariSphere->Transform);
    }*/
}
