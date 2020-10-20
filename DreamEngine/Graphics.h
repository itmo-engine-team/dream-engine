#pragma once

#include <d3d.h>
#include <d3d11_1.h>
#include <d2d1.h>
#include <dwrite.h>

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

#pragma comment(lib, "d2d1.lib") // This is what D2D1CreateFactory makes to work
#pragma comment(lib, "d2d1.lib") // This is what D2D1CreateFactory makes to work
#pragma comment(lib, "Dwrite") // This is what DWriteCreateFactory makes to work

#pragma comment(lib,"d3dcompiler.lib")

#pragma comment(lib,"dwrite.lib")
#pragma comment(lib,"d3d11.lib")

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "RuntimeObject.lib")

class Graphics
{
public:

    Graphics();
    bool DirectXInitialize(int screenWidth, int screenHeight, HWND hWnd);
    
    bool DrawTextOnScene(FLOAT posX, FLOAT posY, const wchar_t* wszText);

    void CreateImGuiFrame();

    ID3D11Device* GetDevice();
    ID3D11DeviceContext* GetContext();
    IDXGISwapChain* GetSwapChain();
    ID3D11RenderTargetView* GetRenderTargetView();
    ID3DUserDefinedAnnotation* GetAnnotation();
    ID3D11RasterizerState* GetRasterState();
    ID3D11RasterizerState* GetShadowRasterState();

    ID3D11Texture2D* GetDepthStencil();
    ID3D11DepthStencilView* GetDepthStencilView();
    
    // Variables for Shadows
    ID3D11Texture2D* shadowMap = nullptr;
    ID3D11DepthStencilView* shadowDepthView = nullptr;
    ID3D11ShaderResourceView* shadowResourceView = nullptr;
    D3D11_VIEWPORT* shadowViewport;

    D3D11_VIEWPORT* GetShadowViewport() const;

private:
   
    ID3D11Device* device;
    ID3D11DeviceContext* context;
    IDXGISwapChain* swapChain;
    ID3D11RenderTargetView* renderTargetView;
    ID3DUserDefinedAnnotation* annotation;
    ID3D11RasterizerState* rasterState;
    ID3D11RasterizerState* shadowRasterState;

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
    void setupImGui(HWND hWnd);

    bool initDepthShaderMap();


};