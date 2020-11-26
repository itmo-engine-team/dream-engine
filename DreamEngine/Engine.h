#pragma once

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

#include <iostream>

#include "Graphics.h"
#include "SimpleMath.h"
#include "MeshRenderer.h"
#include "Window.h"

#include "GameAssetManager.h"
#include "Game.h"

#include "InputSystem.h"
#include "OrthoWindow.h"

using namespace DirectX::SimpleMath;

class Editor;

class Engine
{
public:

    Engine(Game* game, InputSystem* inputSystem, HINSTANCE hInstance, WNDCLASSEX wc);
    ~Engine();

    void Init();

    bool ProcessWndMessage(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);

    void DoFrame();

    Game* GetGame() const;

    Graphics* GetGraphics() const;
    Window* GetWindow() const;
    GameAssetManager* GetGameAssetManager() const;
    MeshRenderer* GetMeshRenderer() const;

    InputSystem* GetInputSystem() const;

    float GetDeltaTime() const;
    int GetScreenWidth() const;
    int GetScreenHeight() const;

protected:

    bool isGameMode = false;

    Game* game;
    Editor* editor;

    Window* window;
    Graphics* graphics;
    GameAssetManager* gameAssetManager;
    MeshRenderer* meshRenderer;

    OrthoWindow* orthoWindow;

    InputSystem* inputSystem = nullptr;

    float deltaTime = 0;
    float currentTime = 0;

    int screenWidth = 0;
    int screenHeight = 0;

    DWORD dwStartTick;

    virtual void update();
    void render();
    void renderScene();

};