#include "Engine.h"

#include "Graphics.h"
#include "Editor.h"
#include "AssetManager.h"

#include "ConstantBuffer.h"
#include "AssetService.h"
#include "EngineConfigInfo.h"

#include "Game.h"
#include "ModelViewer.h"
#include "ActorViewer.h"
#include <iostream>

Engine* Engine::INSTANCE = nullptr;

Engine::Engine()
{
    WNDCLASSEX wc;
    wc.lpfnWndProc = WndProc;

    inputSystem = new InputSystem();

    engineConfigInfo = AssetService::DeserializeFromFile<EngineConfigInfo>("Engine/config.json");
    isGameMode = engineConfigInfo->IsGameMode();

    dwStartTick = GetTickCount();

    window = new Window(engineConfigInfo->GetScreenWidth(), engineConfigInfo->GetScreenHeight());
    window->WindowInitialize(GetModuleHandle(nullptr), wc);

    graphics = new Graphics(window);

    assetManager = new AssetManager();
    game = new Game(engineConfigInfo, inputSystem, graphics, assetManager);

    modelViewer = new ModelViewer(engineConfigInfo, inputSystem, graphics, assetManager);
    actorViewer = new ActorViewer(engineConfigInfo, inputSystem, graphics, assetManager);
    editor = new Editor(
        new EditorContext(graphics, assetManager, game, modelViewer, actorViewer));

    Init();

    INSTANCE = this;
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
    actorViewer->Init();
}

bool Engine::ProcessWndMessage(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
    inputSystem->ProcessWndMessage(hwnd, umessage, wparam, lparam);

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
    actorViewer->Update(deltaTime);
    editor->Update();
}

void Engine::render()
{
    game->RenderPipeline();

    if (!isGameMode)
    {
        modelViewer->RenderPipeline();
        actorViewer->RenderPipeline();

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

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
    if (ImGui_ImplWin32_WndProcHandler(hwnd, umessage, wparam, lparam))
    {
        return true;
    }

    if (Engine::INSTANCE != nullptr && Engine::INSTANCE->ProcessWndMessage(hwnd, umessage, wparam, lparam))
    {
        return true;
    }

    switch (umessage)
    {
        // Check if the window is being destroyed.
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
        // Check if the window is being closed.
    case WM_CLOSE:
        PostQuitMessage(0);
        return 0;
    case WM_SIZE:
        std::cout << "Width " << LOWORD(lparam) << " Height " << HIWORD(lparam) << std::endl;
        return 0;
    case WM_KEYDOWN:
        if (wparam == 27) PostQuitMessage(0);
        break;

        // All other messages pass to the message handler in the system class.
    default:
        return DefWindowProc(hwnd, umessage, wparam, lparam);
    }
}
