#include "KatamariGame.h"
#include <iostream>
#include "KatamariCamera.h"
#include "Engine/Texture.h"
#include "Engine/StaticModelComponent.h"

using namespace DirectX::SimpleMath;

KatamariGame::KatamariGame(HINSTANCE hInstance, WNDCLASSEX wc) : Game(hInstance, wc)
{
	
}

KatamariGame::~KatamariGame()
{
}

void KatamariGame::init()
{
	// Init Shaders
	texture = new Texture(this, L"Meshes/eyeball/eyes_blue.jpg");

	D3D11_INPUT_ELEMENT_DESC texturedShaderInputElements[] = {
		D3D11_INPUT_ELEMENT_DESC {
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			0,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
		D3D11_INPUT_ELEMENT_DESC {
			"COLOR",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
		D3D11_INPUT_ELEMENT_DESC {
			"NORMAL",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
		D3D11_INPUT_ELEMENT_DESC {
			"TEXCOORD",
			0,
			DXGI_FORMAT_R32G32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
	};

	texturedShader = new TexturedShader(this, L"Shaders/ShaderTextured.fx", texturedShaderInputElements, 4, texture);

	D3D11_INPUT_ELEMENT_DESC shaderInputElements[] = {
		D3D11_INPUT_ELEMENT_DESC {
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			0,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
		D3D11_INPUT_ELEMENT_DESC {
			"COLOR",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
		D3D11_INPUT_ELEMENT_DESC {
			"NORMAL",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
	};

	shader = new Shader(this, L"Shaders/Shader.fx", shaderInputElements, 3);

	// Init Meshes

	planeModel = MeshRenderer::CreateBoxModel(shader, { 1, 1, 1, 1 }, { 2, 0.1, 2 });
	boxModel = MeshRenderer::CreateBoxModel(shader, { 1, 1, 1, 1 }, { 0.1, 0.1, 0.1 });
	playerModel = new ModelData(meshRenderer, "Meshes/eyeball/eyeball-mod.obj", texturedShader);

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

	camera = new KatamariCamera(this, {0, 1, -6}, katamariPlayer);
}

void KatamariGame::update()
{
	while (const auto delta = mouse->ReadRawDelta())
	{
		camera->rotate((float)delta->x * -deltaTime, (float)delta->y * deltaTime);
	}

	if (inputDevice->KeyIsPressed('W'))
	{
		if (inputDevice->KeyIsPressed('E'))
		{
			camera->translate({ 0.0f,0.0f,deltaTime });
		}
		else 
		{
			katamariPlayer->GetTransform()->AddWorldPosition({ 0.0f, 0.0f, deltaTime });
			katamariPlayer->GetTransform()->AddWorldRotation({ 1, 0, 0 }, deltaTime);
		}		
	}
	if (inputDevice->KeyIsPressed('A'))
	{
		if (inputDevice->KeyIsPressed('E'))
		{
			camera->translate({ deltaTime,0.0f,0.0f });
		}
		else 
		{
			katamariPlayer->GetTransform()->AddWorldPosition({ deltaTime, 0.0f, 0.0f });
			katamariPlayer->GetTransform()->AddWorldRotation({ 0, 0, 1 }, -deltaTime);
		}
	}
	if (inputDevice->KeyIsPressed('S'))
	{
		if (inputDevice->KeyIsPressed('E'))
		{
			camera->translate({ 0.0f,0.0f,-deltaTime });
		}
		else
		{
			katamariPlayer->GetTransform()->AddWorldPosition({ 0.0f, 0.0f, -deltaTime });
			katamariPlayer->GetTransform()->AddWorldRotation({ 1, 0, 0 }, -deltaTime);
		}
	}
	if (inputDevice->KeyIsPressed('D'))
	{
		if (inputDevice->KeyIsPressed('E'))
		{
			camera->translate({ -deltaTime,0.0f,0.0f });
		}
		else
		{
			katamariPlayer->GetTransform()->AddWorldPosition({ -deltaTime, 0.0f, 0.0f });
			katamariPlayer->GetTransform()->AddWorldRotation({ 0, 0, 1 }, deltaTime);
		}
	}

	katamariPlayer->Update();
	camera->update();

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
	/*if (!gameObject->transform->HasParent() && katamariSphere->collider->Contains(gameObject->transform->GetWorldPosition()))
	{
		gameObject->transform->SetParent(katamariSphere->transform);
	}*/
}
