#pragma once
#include <d3d11_1.h>
#include "InputDevice.h"
#include "SimpleMath.h"
#include "Camera.h"
#include "Mouse.h"
#include "MeshRenderer.h"
#include "Window.h"
#include "Graphics.h"

using namespace DirectX::SimpleMath;

class Game
{
public:
	Game(HINSTANCE hInstance, WNDCLASSEX wc);
	virtual ~Game();

	virtual void init();
	
	float deltaTime = 0;
	float currentTime = 0;

	int screenWidth = 0;
	int screenHeight = 0;

	HWND hWnd;

	InputDevice* inputDevice;
	ID3DUserDefinedAnnotation* annotation;
	
	Mouse* mouse;
	
	void doFrame();

	Camera* camera;
	MeshRenderer* meshRenderer;
	Graphics* graphics;
protected:
	Window* window;
	
	virtual void update();
	void render();
	virtual void drawObjects();
};

