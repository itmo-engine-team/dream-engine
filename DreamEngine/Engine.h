#pragma once

#include "SimpleMath.h"
#include "MeshRenderer.h"
#include "Window.h"

#include "GameAssetManager.h"
#include "Game.h"

#include "InputSystem.h"
#include "OrthoWindow.h"
#include "ModelViewer.h"

using namespace DirectX::SimpleMath;

class AssetManager;
class Graphics;
class Editor;
class EngineConfigInfo;

class Engine
{
public:

    Engine(InputSystem* inputSystem, HINSTANCE hInstance, WNDCLASSEX wc);
    ~Engine();

    void Init();

    bool ProcessWndMessage(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);

    void DoFrame();

    Game* GetGame() const;
    AssetManager* GetAssetManager() const;

    Graphics* GetGraphics() const;
    GameAssetManager* GetGameAssetManager() const;
    MeshRenderer* GetMeshRenderer() const;

    InputSystem* GetInputSystem() const;

    float GetDeltaTime() const;

protected:

    bool isGameMode = true;

    EngineConfigInfo* engineConfigInfo;

    Game* game;
    ModelViewer* modelViewer;
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
    void renderScene();

};