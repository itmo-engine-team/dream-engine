#pragma once

#include "Graphics.h"
#include "InputDevice.h"
#include "SimpleMath.h"
#include "Camera.h"
#include "Mouse.h"
#include "MeshRenderer.h"
#include "Window.h"

using namespace DirectX::SimpleMath;

class Game
{
public:
	Game(HINSTANCE hInstance, WNDCLASSEX wc);
	virtual ~Game();

	virtual void init();
	Graphics* GetGraphics();
	
	float deltaTime = 0;
	float currentTime = 0;

	int screenWidth = 0;
	int screenHeight = 0;

	HWND hWnd;

	InputDevice* inputDevice;
	
	Mouse* mouse;
	
	void doFrame();

	Camera* camera;
	MeshRenderer* meshRenderer;
	
protected:
	Window* window;
	Graphics* graphics;

	virtual void update();
	void render();
	virtual void drawObjects();
};