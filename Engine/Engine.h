#pragma once

#include <iostream>

#include "Graphics/Graphics.h"
#include "SimpleMath.h"
#include "Graphics/MeshRenderer.h"
#include "Graphics/Window.h"

#include "Input/InputDevice.h"
#include "Input/Mouse.h"

#include "GameAssetManager/GameAssetManager.h"
#include "Game.h"

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