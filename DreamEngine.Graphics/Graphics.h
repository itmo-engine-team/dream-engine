#pragma once

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "RuntimeObject.lib")

#pragma comment(lib, "d2d1.lib") // This is what D2D1CreateFactory makes to work
#pragma comment(lib, "Dwrite") // This is what DWriteCreateFactory makes to work
#pragma comment(lib,"dwrite.lib")

#include <d3d.h>
#include <d3d11_1.h>
#include <d2d1.h>
#include <dwrite.h>

#include "Shader.h"
#include "Window.h"
#include "LightShader.h"
#include "ModelShader.h"
#include "OrthoWindow.h"

class MeshRenderer;

class Graphics
{
public:

    Graphics(Window* window);
    ~Graphics();
    
    bool DrawTextOnScene(FLOAT posX, FLOAT posY, const wchar_t* wszText);
    
    void PrepareRenderBackBuffer();
    void PrepareRenderShadowMap() const;
    void PrepareRenderSceneMap();
    void PrepareRenderScene();

    Window* GetWindow() const;
    OrthoWindow* GetOrthoWindow() const;
  
    ID3D11Device* GetDevice();
    ID3D11DeviceContext* GetContext();
    IDXGISwapChain* GetSwapChain();
    ID3D11RenderTargetView* GetBackBufferRenderTargetView();
    ID3DUserDefinedAnnotation* GetAnnotation();

    ID3D11Texture2D* GetDepthStencil();
    ID3D11DepthStencilView* GetDepthStencilView();

    LightShader* GetLightShader();
    ModelShader* GetModelShader();

    MeshRenderer* GetMeshRenderer() const;

    bool HasLight() const;
    bool HasShadow() const;

private:

    const FLOAT SHADOW_MAP_SIZE = 1024;

    std::wstring graphicsPath;

    Window* window;
    OrthoWindow* orthoWindow;

    ID3D11Device* device;
    ID3D11DeviceContext* context;
    IDXGISwapChain* swapChain;
    ID3DUserDefinedAnnotation* annotation;
    ID3D11RasterizerState* rasterState;

    ID3D11Texture2D* depthStencil = nullptr;                     // Depth buffer texture
    ID3D11DepthStencilView* depthStencilView = nullptr;          // View object, depth buffer
    Shader* depthShader;

    ID3D11RenderTargetView* backBufferRenderTargetView;
    D3D11_VIEWPORT viewport;

    // Variables for Shadows
    ID3D11SamplerState* shadowSamplerState = nullptr;

    // Variables for Direct2D initialization
    ID2D1Factory* factory = nullptr;
    ID2D1RenderTarget* renderTarget;
    ID2D1SolidColorBrush* brush = nullptr;

    IDWriteFactory* writeFactory = nullptr;
    IDWriteTextFormat* textFormat;
    
    LightShader* lightShader;
    ModelShader* modelShader;

    MeshRenderer* meshRenderer;

    bool hasLight = true;
    bool hasShadow = false;

    bool initDirectX();
    void initShaders();
    bool initDirect2D();
    void initImGui();

    void configureBrush(FLOAT posX, FLOAT posY, const wchar_t* wszText);
  
    bool initDepthShadowMap(); 
};
