#pragma once
#include <d3d.h>
#include <d3d11.h>
#include <iostream>

#define ZCHECK(exp) if(FAILED(exp)) { printf("Check failed at file: %s at line %i", __FILE__, __LINE__); return 0; }

class Game;

class Graphics
{
public:
    Graphics(Game* currentGame);
	
	ID3D11Device* device;
	ID3D11DeviceContext* context;
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* rtv;

	ID3D11Texture2D* depthStencil = NULL;             // Текстура буфера глубин
	ID3D11DepthStencilView* depthStencilView = NULL;          // Объект вида, буфер глубин
	
	bool DirectXInitialize();

private:
    Game* game;
};

