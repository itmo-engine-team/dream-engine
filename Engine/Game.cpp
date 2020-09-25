#include "Game.h"
#include <iostream>

Game::Game(HINSTANCE hInstance, WNDCLASSEX wc)
{   
	graphics = new Graphics(this);
	inputDevice = new InputDevice();

	mouse = new Mouse();
	mouse->EnableRaw();
	meshRenderer = new MeshRenderer();
	window = new Window(this);
	window->WindowInitialize(hInstance, wc);
	
	graphics->DirectXInitialize();
}

Game::~Game()
{

}

void Game::init()
{
	
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
	graphics->context->ClearRenderTargetView(graphics->rtv, color);
	graphics->context->ClearDepthStencilView(graphics->depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	annotation->BeginEvent(L"BeginDraw");
	drawObjects();
	annotation->EndEvent();
	
	graphics->swapChain->Present(1, 0);
}

void Game::drawObjects()
{
	
}
