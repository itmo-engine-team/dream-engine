#include "Engine.h"
#include <iostream>

Engine::Engine(HINSTANCE hInstance, WNDCLASSEX wc)
{
	screenWidth = 1200;
	screenHeight = 800;

    dwStartTick = GetTickCount();

    inputDevice = new InputDevice();

	mouse = new Mouse();
	mouse->EnableRaw();

	meshRenderer = new MeshRenderer();

	window = new Window(this);
	window->WindowInitialize(hInstance, wc);

	graphics = new Graphics();
	graphics->DirectXInitialize(screenWidth, screenHeight, window->GetWnd());
}

Engine::~Engine()
{

}

void Engine::Init()
{
	
}

Graphics* Engine::GetGraphics() const
{
	return graphics;
}

Window* Engine::GetWindow() const
{
	return window;
}

void Engine::DoFrame()
{
	// Calculate current time and delta time	
    const DWORD dwCurrentTick = GetTickCount();
	float t = (dwCurrentTick - dwStartTick) / 1000.0f;
	deltaTime = t - currentTime;
	currentTime = t;

	std::cout << deltaTime << std::endl;

	update();
	render();
}

float Engine::GetDeltaTime() const
{
	return deltaTime;
}

int Engine::GetScreenWidth() const
{
	return screenWidth;
}

int Engine::GetScreenHeight() const
{
	return screenHeight;
}

Camera* Engine::GetCamera() const
{
	return camera;
}

InputDevice* Engine::GetInputDevice() const
{
	return inputDevice;
}

Mouse* Engine::GetMouse() const
{
	return mouse;
}

void Engine::update()
{
	
}

void Engine::render()
{
	float color[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	graphics->GetContext()->ClearRenderTargetView(graphics->GetRenderTargetView(), color);
	graphics->GetContext()->ClearDepthStencilView(graphics->GetDepthStencilView(), D3D11_CLEAR_DEPTH, 1.0f, 0);

	graphics->GetAnnotation()->BeginEvent(L"BeginDraw");
	drawObjects();
	graphics->GetAnnotation()->EndEvent();
	
	graphics->GetSwapChain()->Present(1, 0);
}

void Engine::drawObjects()
{
	
}
