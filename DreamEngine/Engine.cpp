#include "Engine.h"

#include "Graphics.h"
#include "Editor.h"
#include "AssetManager.h"

#include "ConstantBuffer.h"
#include "LightBuffer.h"
#include "AssetService.h"
#include "EngineConfigInfo.h"

#include "Game.h"
#include "ACS_Light.h"

Engine::Engine(InputSystem* inputSystem, HINSTANCE hInstance, WNDCLASSEX wc) 
    : inputSystem(inputSystem)
{
    engineConfigInfo = AssetService::DeserializeFromFile<EngineConfigInfo>("Engine/config.json");
    isGameMode = engineConfigInfo->IsGameMode();

    dwStartTick = GetTickCount();

    window = new Window(engineConfigInfo->GetScreenWidth(), engineConfigInfo->GetScreenHeight());
    window->WindowInitialize(hInstance, wc);

    graphics = new Graphics(window);

    assetManager = new AssetManager();
    game = new Game(engineConfigInfo, inputSystem, graphics);
    modelViewer = new ModelViewer(engineConfigInfo, inputSystem, graphics);
    editor = new Editor(new EditorContext(graphics, assetManager, game, modelViewer));
}

Engine::~Engine()
{
    delete graphics;
    graphics = nullptr;

    delete window;
    window = nullptr;

    delete inputSystem;
    inputSystem = nullptr;
}

void Engine::Init()
{
    game->Init();
    modelViewer->Init();
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

AssetManager* Engine::GetAssetManager() const
{
    return assetManager;
}

float Engine::GetDeltaTime() const
{
    return deltaTime;
}

void Engine::update()
{
    game->Update(deltaTime);
    modelViewer->Update(deltaTime);
    editor->Update();
}

void Engine::render()
{
    game->RenderPipeline();

    if (!isGameMode)
    {
        // Render editor
        graphics->GetAnnotation()->BeginEvent(L"Editor");
        graphics->PrepareRenderBackBuffer();
        editor->Render();
        graphics->GetAnnotation()->EndEvent();
    }

    /*// Add text on Scene
    wchar_t pretext[200];
    swprintf(pretext, 200, L"Number of unattached objects: %u\nNumber of attached objects: %u", 4, 0);
    graphics->DrawTextOnScene(400, 100, pretext);*/

    graphics->GetSwapChain()->Present(1, 0);
}
