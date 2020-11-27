#include "Engine.h"

#include "Graphics.h"
#include "Editor.h"

#include "ConstantBuffer.h"
#include "LightBuffer.h"

Engine::Engine(Game* game, InputSystem* inputSystem, HINSTANCE hInstance, WNDCLASSEX wc) 
    : game(game), inputSystem(inputSystem)
{
    dwStartTick = GetTickCount();

    meshRenderer = new MeshRenderer();

    gameAssetManager = new GameAssetManager(this);

    window = new Window(1200, 800);
    window->WindowInitialize(hInstance, wc);

    graphics = new Graphics(window);
    graphics->DirectXInitialize();

    orthoWindow = new OrthoWindow(graphics);

    editor = new Editor(graphics->GetDevice(), graphics->GetContext(), window->GetWnd());
}

Engine::~Engine()
{
    delete graphics;
    graphics = nullptr;

    delete window;
    window = nullptr;

    delete meshRenderer;
    meshRenderer = nullptr;

    delete inputSystem;
    inputSystem = nullptr;
}

void Engine::Init()
{
    // Init Game
    game->Init(this);
    orthoWindow->Initialize(graphics->GetDevice(),
        graphics->GetWindow()->GetScreenWidth(), graphics->GetWindow()->GetScreenHeight());
}

bool Engine::ProcessWndMessage(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
    switch (umessage)
    {
        case WM_PAINT:
            DoFrame();
            return true;
        default:
            break;
    }

    return false;
}

Graphics* Engine::GetGraphics() const
{
    return graphics;
}

GameAssetManager* Engine::GetGameAssetManager() const
{
    return gameAssetManager;
}

MeshRenderer* Engine::GetMeshRenderer() const
{
    return meshRenderer;
}

InputSystem* Engine::GetInputSystem() const
{
    return inputSystem;
}

void Engine::DoFrame()
{
    // Calculate current time and delta time	
    const DWORD dwCurrentTick = GetTickCount();
    float t = (dwCurrentTick - dwStartTick) / 1000.0f;
    deltaTime = t - currentTime;
    currentTime = t;
    if(deltaTime > 1)
    {
        deltaTime = 0.0166;
    }

    update();
    render();
}

Game* Engine::GetGame() const
{
    return game;
}

float Engine::GetDeltaTime() const
{
    return deltaTime;
}

void Engine::update()
{
    game->Update();
    editor->Update();
}

void Engine::render()
{
    // Deferred renders to textures
    graphics->PrepareDeferredBuffer();

    graphics->GetAnnotation()->BeginEvent(L"Deferred");
    game->Render();
    graphics->GetAnnotation()->EndEvent();

    // Render shadow map
    graphics->GetAnnotation()->BeginEvent(L"ShadowMap");
    graphics->PrepareRenderShadowMap();
    game->RenderShadowMap();
    graphics->GetAnnotation()->EndEvent();

    if (isGameMode)
    {
        graphics->PrepareRenderScene();
        renderScene();
    }
    else
    {
        graphics->PrepareRenderSceneMap();

        renderScene();

        graphics->PrepareRenderScene();
        editor->Render();
    }

    /*// Add text on Scene
    wchar_t pretext[200];
    swprintf(pretext, 200, L"Number of unattached objects: %u\nNumber of attached objects: %u", 4, 0);
    graphics->DrawTextOnScene(400, 100, pretext);*/

    graphics->GetSwapChain()->Present(1, 0);
}

void Engine::renderScene()
{
    graphics->GetAnnotation()->BeginEvent(L"Scene");

    const ConstantBuffer cb =
    {
        Matrix::Identity,
        Matrix::Identity,
        Matrix::Identity,
        game->GetLight()->GetViewMatrix(),
        game->GetLight()->GetProjectionMatrix(),
    };

    const LightBuffer lb =
    {
        Vector4{0.15f, 0.15f, 0.15f, 1.0f},
        Vector4{1.0f, 1.0f, 1.0f, 1.0f},
        game->GetLight()->GetDirection(),
        100.0f,
        {1.0f, 1.0f, 1.0f, 1.0f }
    };

    orthoWindow->Render(graphics->GetContext(), cb, lb);
    graphics->GetAnnotation()->EndEvent();
}
