#include "KatamariGame.h"

#include <iostream>

#include "Graphics/Shader/Texture.h"
#include "GameObject/Component/StaticModelComponent.h"

using namespace DirectX::SimpleMath;

KatamariGame::KatamariGame(HINSTANCE hInstance, WNDCLASSEX wc) : Engine(hInstance, wc)
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

void KatamariGame::Init()
{
    // Init Shaders

    texture = new Texture(this, L"Game/Meshes/eyeball/eyes_blue.jpg");
    texturedShader = new TexturedShader(this, L"Game/Shaders/ShaderTextured.fx", texture);
    texturedShader->Init();

    shader = new Shader(this, L"Game/Shaders/Shader.fx");
    shader->Init();

    // Init Meshes

    planeModel = MeshRenderer::CreateBoxModel(shader, { 1, 1, 1, 1 }, { 2, 0.1, 2 });
    boxModel = MeshRenderer::CreateBoxModel(shader, { 1, 1, 1, 1 }, { 0.1, 0.1, 0.1 });
    playerModel = new ModelData(meshRenderer, "Game/Meshes/eyeball/eyeball-mod.obj", texturedShader);

    // Init objects

    plane = new Actor(this, new Transform({ 0, 0, 0 }));
    plane->AddComponent(new StaticModelComponent(this, plane, new Transform({ 0, 0, 0 }), planeModel));

    box1 = new Actor(this, new Transform({ -1, 1, 0 }));
    box1->AddComponent(new StaticModelComponent(this, box1, new Transform({ 0, 0, 0 }), boxModel));

    box2 = new Actor(this, new Transform({ -0.5, 1, -1 }));
    box2->AddComponent(new StaticModelComponent(this, box2, new Transform({ 0, 0, 0 }), boxModel));

    box3 = new Actor(this, new Transform({ 1, 1, 0 }));
    box3->AddComponent(new StaticModelComponent(this, box3, new Transform({ 0, 0, 0 }), boxModel));

    katamariPlayer = new KatamariSphere(this, new Transform({ 0, 0.8, 0 }));
    playerSphere = new StaticModelComponent(this, katamariPlayer, new Transform({ 0, 0, 0 }), playerModel);
    katamariPlayer->AddComponent(playerSphere);

    spectatorActor = new SpectatorActor(this, new Transform({ 0, 1, -6 }));
}

void KatamariGame::update()
{
    katamariPlayer->Update();
    spectatorActor->Update();

    // Update player movement
    if (inputDevice->KeyIsPressed('C')) return; // Skip if camera moves
    if (inputDevice->KeyIsPressed('W'))
    {
        katamariPlayer->GetTransform()->AddWorldPosition({ 0.0f, 0.0f, deltaTime });
        playerSphere->GetTransform()->AddRelativeRotation({ 1, 0, 0 }, deltaTime);
    }
    if (inputDevice->KeyIsPressed('A'))
    {
        katamariPlayer->GetTransform()->AddWorldPosition({ deltaTime, 0.0f, 0.0f });
        playerSphere->GetTransform()->AddRelativeRotation({ 0, 0, 1 }, -deltaTime);
    }
    if (inputDevice->KeyIsPressed('S'))
    {
        katamariPlayer->GetTransform()->AddWorldPosition({ 0.0f, 0.0f, -deltaTime });
        playerSphere->GetTransform()->AddRelativeRotation({ 1, 0, 0 }, -deltaTime);
    }
    if (inputDevice->KeyIsPressed('D'))
    {
        katamariPlayer->GetTransform()->AddWorldPosition({ -deltaTime, 0.0f, 0.0f });
        playerSphere->GetTransform()->AddRelativeRotation({ 0, 0, 1 }, deltaTime);
    }

    /*collisionCheck(box1);
    collisionCheck(box2);
    collisionCheck(box3);*/
}

void KatamariGame::drawObjects()
{
    plane->Draw();
    box1->Draw();
    box2->Draw();
    box3->Draw();
    katamariPlayer->Draw();
}

void KatamariGame::collisionCheck(GameObject* gameObject)
{
    /*if (!gameObject->Transform->HasParent() && katamariSphere->collider->Contains(gameObject->Transform->GetWorldPosition()))
    {
        gameObject->Transform->SetParent(katamariSphere->Transform);
    }*/
}
