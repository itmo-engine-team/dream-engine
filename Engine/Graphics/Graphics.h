#pragma once

#include <d3d.h>
#include <d3d11_1.h>
#include <d2d1.h>
#include <dwrite.h>

#pragma comment(lib, "d2d1.lib") // This is what D2D1CreateFactory makes to work
#pragma comment(lib, "Dwrite") // This is what DWriteCreateFactory makes to work

class Graphics
{
public:

    Graphics();
    bool DirectXInitialize(int screenWidth, int screenHeight, HWND hWnd);
    
    bool DrawTextOnScene(FLOAT posX, FLOAT posY, const wchar_t* wszText);

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

    ID3D11Texture2D* depthStencil = nullptr;                     // Depth buffer texture
    ID3D11DepthStencilView* depthStencilView = nullptr;          // View object, depth buffer

    // Variables for Direct2D initialization
    ID2D1Factory* factory = nullptr;
    ID2D1RenderTarget* renderTarget;
    ID2D1SolidColorBrush* brush = nullptr;

    IDWriteFactory* writeFactory = nullptr;
    IDWriteTextFormat* textFormat;
    RECT rect;

    bool direct2DInitialize(HWND hWnd);
    void configureBrush(FLOAT posX, FLOAT posY, const wchar_t* wszText);

};