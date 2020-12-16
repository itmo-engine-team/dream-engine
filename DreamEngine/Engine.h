#pragma once

#include "SimpleMath.h"
#include "MeshRenderer.h"
#include "Window.h"

#include "GameAssetManager.h"
#include "Game.h"

#include "InputSystem.h"
#include "OrthoWindow.h"

class AssetManager;
using namespace DirectX::SimpleMath;

class Graphics;
class Editor;
class EngineConfigInfo;

class Engine
{
public:

    Engine(Game* game, InputSystem* inputSystem, HINSTANCE hInstance, WNDCLASSEX wc);
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

    Game* game;
    Editor* editor;
    AssetManager* assetManager;

    EngineConfigInfo* engineConfigInfo;

    Window* window;
    Graphics* graphics;
    
    OrthoWindow* orthoWindow;

    InputSystem* inputSystem = nullptr;

    float deltaTime = 0;
    float currentTime = 0;

    DWORD dwStartTick;

    virtual void update();
    void render();
    void renderScene();

};