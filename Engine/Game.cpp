#include "Game.h"
#include <iostream>

Game::Game(HINSTANCE hInstance, WNDCLASSEX wc)
{   
	inputDevice = new InputDevice();

	mouse = new Mouse();
	mouse->EnableRaw();
	meshRenderer = new MeshRenderer();
	window = new Window(this);
	window->WindowInitialize(hInstance, wc);

	graphics = new Graphics();
	graphics->DirectXInitialize(screenWidth, screenHeight, hWnd);
}

Game::~Game()
{

}

void Game::init()
{
	
}

Graphics* Game::GetGraphics()
{
	return graphics;
}

void Game::doFrame()
{
	update();
	render();
}

void Game::update()
{
	
}

void Game::render()
{
	float color[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	graphics->GetContext()->ClearRenderTargetView(graphics->GetRenderTargetView(), color);
	graphics->GetContext()->ClearDepthStencilView(graphics->GetDepthStencilView(), D3D11_CLEAR_DEPTH, 1.0f, 0);

	graphics->GetAnnotation()->BeginEvent(L"BeginDraw");
	drawObjects();
	graphics->GetAnnotation()->EndEvent();
	
	graphics->GetSwapChain()->Present(1, 0);
}

void Game::drawObjects()
{
	
}
