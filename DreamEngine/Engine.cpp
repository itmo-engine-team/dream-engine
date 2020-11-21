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
    if (graphics->GetGameMode() == true)
    {
        graphics->GetAnnotation()->BeginEvent(L"BeginDraw");
        game->RenderDeferred();
        graphics->GetAnnotation()->EndEvent();
    }
    
    // Render shadow map
    /*graphics->PrepareRenderShadowMap();
    game->RenderShadowMap();*/

    // Render scene
    graphics->PrepareRenderScene();

    // Light rendering
    game->RenderLight();

    graphics->SwitchWindow();

    /*// Add text on Scene
    wchar_t pretext[200];
    swprintf(pretext, 200, L"Number of unattached objects: %u\nNumber of attached objects: %u", 4, 0);
    graphics->DrawTextOnScene(400, 100, pretext);*/
}
