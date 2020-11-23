#pragma once

#include <d3d.h>
#include <d3d11_1.h>
#include <d2d1.h>
#include <dwrite.h>

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "Shader.h"
#include <vector>

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

    void SwitchWindow();
    
    void PrepareRenderScene();
    void PrepareRenderShadowMap() const;
    void PrepareRenderSceneMap(int screenWidth, int screenHeight);
  
    ID3D11Device* GetDevice();
    ID3D11DeviceContext* GetContext();
    IDXGISwapChain* GetSwapChain();
    ID3D11RenderTargetView* GetRenderTargetView();
    ID3DUserDefinedAnnotation* GetAnnotation();

    ID3D11Texture2D* GetDepthStencil();
    ID3D11DepthStencilView* GetDepthStencilView();

    ID3D11Texture2D* GetShadowMap();

    bool HasLight() const;
    bool HasShadow() const;

    bool IsGameMode() const;
    bool IsEditMode() const;

private:

    const FLOAT SHADOW_MAP_SIZE = 1024;

    ID3D11Device* device;
    ID3D11DeviceContext* context;
    IDXGISwapChain* swapChain;
    ID3DUserDefinedAnnotation* annotation;
    ID3D11RasterizerState* rasterState;

    ID3D11Texture2D* depthStencil = nullptr;                     // Depth buffer texture
    ID3D11DepthStencilView* depthStencilView = nullptr;          // View object, depth buffer
    Shader* depthShader;

    ID3D11RenderTargetView* renderTargetView;
    D3D11_VIEWPORT viewport;

    // Variables for Shadows
    ID3D11Texture2D* shadowMap = nullptr;
    ID3D11DepthStencilView* shadowDepthView = nullptr;
    ID3D11ShaderResourceView* shadowResourceView = nullptr;
    ID3D11RasterizerState* shadowRasterState;
    ID3D11SamplerState* shadowSamplerState = nullptr;
    D3D11_VIEWPORT shadowMapViewport;

    // Variables for Direct2D initialization
    ID2D1Factory* factory = nullptr;
    ID2D1RenderTarget* renderTarget;
    ID2D1SolidColorBrush* brush = nullptr;

    IDWriteFactory* writeFactory = nullptr;
    IDWriteTextFormat* textFormat;
    RECT rect;
  
    // Variables for GameRenderMap
    ID3D11Texture2D* sceneMap = nullptr;
    ID3D11RenderTargetView* sceneRenderTargetView;
    ID3D11ShaderResourceView* sceneResourceView = nullptr;
  
    bool hasLight = true;
    bool hasShadow = true;

    bool gameMode = true;
    bool editMode = false;

    bool direct2DInitialize(HWND hWnd);
    void configureBrush(FLOAT posX, FLOAT posY, const wchar_t* wszText);
    void setupImGui(HWND hWnd);
  
    bool initDepthShadowMap(); 
    bool initSceneMap(int screenWidth, int screenHeight);
    
    void createShadowViewport();
    void createGameViewport();

};