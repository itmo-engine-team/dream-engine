#include "Engine.h"

#include "../Game/KatamariGame.h"

Engine::Engine(HINSTANCE hInstance, WNDCLASSEX wc)
{
    screenWidth = 1200;
    screenHeight = 800;

    dwStartTick = GetTickCount();

    inputDevice = new InputDevice();

    mouse = new Mouse();
    mouse->EnableRaw();

    meshRenderer = new MeshRenderer();

    gameAssetManager = new GameAssetManager(this);

    window = new Window(this);
    window->WindowInitialize(hInstance, wc);

    graphics = new Graphics();
    graphics->DirectXInitialize(screenWidth, screenHeight, window->GetWnd());

    // Init Game
    game = new KatamariGame(this);
}

Engine::~Engine()
{
    delete graphics;
    graphics = nullptr;

    delete window;
    window = nullptr;

    delete meshRenderer;
    meshRenderer = nullptr;

    delete mouse;
    mouse = nullptr;

    delete inputDevice;
    inputDevice = nullptr;
}

void Engine::Init()
{

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

void Engine::DoFrame()
{
    // Calculate current time and delta time	
    const DWORD dwCurrentTick = GetTickCount();
    float t = (dwCurrentTick - dwStartTick) / 1000.0f;
    deltaTime = t - currentTime;
    currentTime = t;

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

InputDevice* Engine::GetInputDevice() const
{
    return inputDevice;
}

Mouse* Engine::GetMouse() const
{
    return mouse;
}

void Engine::update()
{
    game->Update();
}

void Engine::render()
{
    float color[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    graphics->GetContext()->ClearRenderTargetView(graphics->GetRenderTargetView(), color);
    graphics->GetContext()->ClearDepthStencilView(graphics->GetDepthStencilView(), D3D11_CLEAR_DEPTH, 1.0f, 0);

    graphics->GetAnnotation()->BeginEvent(L"BeginDraw");
    game->Render();
    graphics->GetAnnotation()->EndEvent();

    // Add text on Scene
    wchar_t pretext[200];
    swprintf(pretext, 200, L"Number of unattached objects: %u\nNumber of attached objects: %u", 4, 0);
    graphics->DrawTextOnScene(400, 100, pretext);

    graphics->GetSwapChain()->Present(1, 0);
}
