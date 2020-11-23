#include "Engine.h"

Engine::Engine(Game* game, InputSystem* inputSystem, HINSTANCE hInstance, WNDCLASSEX wc) 
    : game(game), inputSystem(inputSystem)
{
    screenWidth = 1200;
    screenHeight = 800;

    dwStartTick = GetTickCount();

    meshRenderer = new MeshRenderer();

    gameAssetManager = new GameAssetManager(this);

    window = new Window(this);
    window->WindowInitialize(hInstance, wc);

    orthoWindow = new OrthoWindow(this);

    graphics = new Graphics();
    graphics->DirectXInitialize(screenWidth, screenHeight, window->GetWnd());
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
    orthoWindow->Initialize(graphics->GetDevice(), screenWidth, screenHeight);
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

Window* Engine::GetWindow() const
{
    return window;
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

int Engine::GetScreenWidth() const
{
    return screenWidth;
}

int Engine::GetScreenHeight() const
{
    return screenHeight;
}

void Engine::update()
{
    game->Update();
}

void Engine::render()
{
    // Deferred renders to textures
    game->PrepareDeferredBuffer();

    graphics->GetAnnotation()->BeginEvent(L"Deferred");
    game->RenderDeferred();
    graphics->GetAnnotation()->EndEvent();

    // TODO Move to deferred
    // Render shadow map
    /*graphics->PrepareRenderShadowMap();
    game->RenderShadowMap();*/

    graphics->PrepareRenderScene(); // TODO Clear scene without rendering

    graphics->GetAnnotation()->BeginEvent(L"Scene");
    if (graphics->IsEditMode())
    {
        
        graphics->PrepareRenderSceneMap(screenWidth, screenHeight);

        // Scene rendering
        orthoWindow->Render(graphics->GetContext());
    }
    else if (graphics->IsGameMode())
    {
        // Scene rendering
        orthoWindow->Render(graphics->GetContext());
    }
    graphics->GetAnnotation()->EndEvent();

    graphics->SwitchWindow();

    /*// Add text on Scene
    wchar_t pretext[200];
    swprintf(pretext, 200, L"Number of unattached objects: %u\nNumber of attached objects: %u", 4, 0);
    graphics->DrawTextOnScene(400, 100, pretext);*/
}
