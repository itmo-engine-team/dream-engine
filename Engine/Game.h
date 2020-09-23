#pragma once
#include <d3d11_1.h>
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
	
	float deltaTime = 0;
	float currentTime = 0;

	int screenWidth = 0;
	int screenHeight = 0;

	HWND hWnd;

	ID3D11Device* device;
	ID3D11DeviceContext* context;
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* rtv;
	ID3DUserDefinedAnnotation* annotation;
	ID3D11Texture2D* depthStencil = NULL;             // Текстура буфера глубин
	ID3D11DepthStencilView* depthStencilView = NULL;          // Объект вида, буфер глубин

	InputDevice* inputDevice;
	Mouse* mouse;
	
	void doFrame();

	Camera* camera;
	MeshRenderer* meshRenderer;
	
protected:
	Window* window;
	virtual void update();
	void render();
	virtual void drawObjects();
};

