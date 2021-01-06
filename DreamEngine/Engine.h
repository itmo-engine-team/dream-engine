#pragma once

#include "SimpleMath.h"
#include "Window.h"

#include "InputSystem.h"

using namespace DirectX::SimpleMath;

class AssetManager;
class Graphics;
class Editor;
class EngineConfigInfo;
class Game;
class ModelViewer;
class ActorViewer;

class Engine
{
public:

    static Engine* INSTANCE;

    Engine();
    ~Engine();

    void Init();

    bool ProcessWndMessage(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);

    void DoFrame();

    Game* GetGame() const;
    AssetManager* GetAssetManager() const;
    Graphics* GetGraphics() const;
    InputSystem* GetInputSystem() const;

    float GetDeltaTime() const;

protected:

    bool isGameMode = true;

    EngineConfigInfo* engineConfigInfo;

    Game* game;
    ModelViewer* modelViewer;
    ActorViewer* actorViewer;
    Editor* editor;
    AssetManager* assetManager;

    Window* window;
    Graphics* graphics;

    InputSystem* inputSystem = nullptr;

    float deltaTime = 0;
    float currentTime = 0;

    DWORD dwStartTick;

    virtual void update();
    void render();

};

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);
static LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);