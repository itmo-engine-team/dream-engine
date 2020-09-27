#pragma once

#include "Graphics.h"
#include "InputDevice.h"
#include "SimpleMath.h"
#include "Camera.h"
#include "Mouse.h"
#include "MeshRenderer.h"
#include "Window.h"

using namespace DirectX::SimpleMath;

class Engine
{
public:

    Engine(HINSTANCE hInstance, WNDCLASSEX wc);
    virtual ~Engine();

    virtual void Init();

    void DoFrame();

    Graphics* GetGraphics() const;
    Window* GetWindow() const;

    Camera* GetCamera() const;

    InputDevice* GetInputDevice() const;
    Mouse* GetMouse() const;

    float GetDeltaTime() const;
    int GetScreenWidth() const;
    int GetScreenHeight() const;

protected:

    Window* window;
    Graphics* graphics;
    MeshRenderer* meshRenderer;

    Camera* camera;

    InputDevice* inputDevice;
    Mouse* mouse;

    float deltaTime = 0;
    float currentTime = 0;

    int screenWidth = 0;
    int screenHeight = 0;

    DWORD dwStartTick;

    virtual void update();
    void render();
    virtual void drawObjects();

};