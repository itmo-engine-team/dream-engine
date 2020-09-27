#pragma once

#include <d3d.h>
#include <d3d11_1.h>
#include <iostream>

#define ZCHECK(exp) if(FAILED(exp)) { printf("Check failed at file: %s at line %i", __FILE__, __LINE__); return 0; }

class Graphics
{
public:

    Graphics();
    bool DirectXInitialize(int screenWidth, int screenHeight, HWND hWnd);

    ID3D11Device* GetDevice();
    ID3D11DeviceContext* GetContext();
    IDXGISwapChain* GetSwapChain();
    ID3D11RenderTargetView* GetRenderTargetView();
    ID3DUserDefinedAnnotation* GetAnnotation();

    ID3D11Texture2D* GetDepthStencil();
    ID3D11DepthStencilView* GetDepthStencilView();

private:

    ID3D11Device* device;
    ID3D11DeviceContext* context;
    IDXGISwapChain* swapChain;
    ID3D11RenderTargetView* renderTargetView;
    ID3DUserDefinedAnnotation* annotation;

    ID3D11Texture2D* depthStencil = NULL;                     // Depth buffer texture
    ID3D11DepthStencilView* depthStencilView = NULL;          // View object, depth buffer

};

