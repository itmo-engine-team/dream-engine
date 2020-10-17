#pragma once

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

#include <iostream>

#include "Graphics/Graphics.h"
#include "SimpleMath.h"
#include "Graphics/MeshRenderer.h"
#include "Graphics/Window.h"

#include "Input/InputDevice.h"
#include "Input/Mouse.h"

#include "InGame/GameAssetManager/GameAssetManager.h"
#include "InGame/Game.h"

using namespace DirectX::SimpleMath;

class Engine
{
public:

    Engine(HINSTANCE hInstance, WNDCLASSEX wc);
    ~Engine();

    void Init();

    void DoFrame();

    Game* GetGame() const;

    Graphics* GetGraphics() const;
    Window* GetWindow() const;
    GameAssetManager* GetGameAssetManager() const;
    MeshRenderer* GetMeshRenderer() const;

    InputDevice* GetInputDevice() const;
    Mouse* GetMouse() const;

    float GetDeltaTime() const;
    int GetScreenWidth() const;
    int GetScreenHeight() const;

protected:

    Game* game;

    Window* window;
    Graphics* graphics;
    GameAssetManager* gameAssetManager;
    MeshRenderer* meshRenderer;

    InputDevice* inputDevice;
    Mouse* mouse;

    float deltaTime = 0;
    float currentTime = 0;

    int screenWidth = 0;
    int screenHeight = 0;

    DWORD dwStartTick;

    virtual void update();
    void render();

};