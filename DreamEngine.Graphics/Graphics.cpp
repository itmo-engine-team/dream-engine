#include "Graphics.h"

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#include "ErrorLogger.h"
#include "DepthShader.h"
#include "MeshRenderer.h"
#include "OrthoWindow.h"

Graphics::Graphics(Window* window) : window(window)
{
    meshRenderer = new MeshRenderer();

    std::string solutionPath = SOLUTION_DIR;
    graphicsPath = std::wstring(solutionPath.begin(), solutionPath.end())
        + L"DreamEngine.Graphics/";

    initDirectX();
}

Graphics::~Graphics()
{
    delete meshRenderer;
    meshRenderer = nullptr;
}

bool Graphics::initDirectX()
{
    HRESULT res;

    DXGI_SWAP_CHAIN_DESC swapDesc = {};
    swapDesc.BufferCount = 1;
    swapDesc.BufferDesc.Width = window->GetScreenWidth();
    swapDesc.BufferDesc.Height = window->GetScreenHeight();
    swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapDesc.OutputWindow = window->GetWnd();
    swapDesc.Windowed = true;
    swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    swapDesc.Flags = 0;
    swapDesc.SampleDesc.Count = 1;
    swapDesc.SampleDesc.Quality = 0;

    D3D_FEATURE_LEVEL featureLevel[] = { D3D_FEATURE_LEVEL_11_1 };
    res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
        D3D11_CREATE_DEVICE_BGRA_SUPPORT, featureLevel, 1, D3D11_SDK_VERSION,
        &swapDesc, &swapChain, &device, nullptr, &context);
    ErrorLogger::DirectXLog(res, Error, "Failed to create device and swapchain", __FILE__, __FUNCTION__, __LINE__);

    ID3D11Texture2D* backTex;
    res = swapChain->GetBuffer(0, IID_ID3D11Texture2D, (void**)&backTex);
    ErrorLogger::DirectXLog(res, Error, "Failed to initialize BackBuffer", __FILE__, __FUNCTION__, __LINE__);
    res = device->CreateRenderTargetView(backTex, nullptr, &backBufferRenderTargetView);
    ErrorLogger::DirectXLog(res, Error, "Failed to create RenderTargetView", __FILE__, __FUNCTION__, __LINE__);

    context->QueryInterface(IID_ID3DUserDefinedAnnotation, (void**)&annotation);

    ID3D11Debug* debug;
    device->QueryInterface(IID_ID3D11Debug, (void**)&debug);

    CD3D11_RASTERIZER_DESC rastDesc = {};
    rastDesc.CullMode = D3D11_CULL_NONE;
    rastDesc.FillMode = D3D11_FILL_SOLID;

    res = device->CreateRasterizerState(&rastDesc, &rasterState); 
    ErrorLogger::DirectXLog(res, Error, 
        "Failed to create RasterizerState", __FILE__, __FUNCTION__, __LINE__);

    // Structure with parameters: 
    D3D11_TEXTURE2D_DESC descDepth;
    ZeroMemory(&descDepth, sizeof(descDepth));
    descDepth.Width = window->GetScreenWidth();
    descDepth.Height = window->GetScreenHeight();
    descDepth.MipLevels = 1;                         
    descDepth.ArraySize = 1;
    descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    descDepth.SampleDesc.Count = 1;
    descDepth.SampleDesc.Quality = 0;
    descDepth.Usage = D3D11_USAGE_DEFAULT;
    descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    descDepth.CPUAccessFlags = 0;
    descDepth.MiscFlags = 0;

    // Using the filled-in description structure, create a texture object
    device->CreateTexture2D(&descDepth, NULL, &depthStencil);

    // Creating a depth buffer object
    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
    ZeroMemory(&descDSV, sizeof(descDSV));
    descDSV.Format = descDepth.Format;
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    descDSV.Texture2D.MipSlice = 0;

    // Using the filled-in description structure and texture, create depth buffer object
    device->CreateDepthStencilView(depthStencil, &descDSV, &depthStencilView);

    viewport = {};
    viewport.Width = window->GetScreenWidth();
    viewport.Height = window->GetScreenHeight();
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.MinDepth = 0;
    viewport.MaxDepth = 1.0f;

    initShaders();
    initDepthShadowMap();

    initDirect2D();
    initImGui();

    orthoWindow = new OrthoWindow(this);
    orthoWindow->Initialize(device, window->GetScreenWidth(), window->GetScreenHeight());

    return true;
}

bool Graphics::initDirect2D()
{
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);

    ID3D11Resource* res;
    this->backBufferRenderTargetView->GetResource(&res);

    IDXGISurface* surface;
    res->QueryInterface(__uuidof(IDXGISurface), reinterpret_cast<void**>(&surface));

    factory->CreateDxgiSurfaceRenderTarget(
        surface,
        D2D1_RENDER_TARGET_PROPERTIES{
            D2D1_RENDER_TARGET_TYPE_HARDWARE,
            D2D1_PIXEL_FORMAT{DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED},
            static_cast<FLOAT>(96),
            static_cast<FLOAT>(96),
        }, &renderTarget);

    res->Release();
    surface->Release();

    HRESULT rs = renderTarget->CreateSolidColorBrush(D2D1_COLOR_F{0.4f, 1.0f, 1.0f, 1.0f}, &brush);

    DWriteCreateFactory(
        DWRITE_FACTORY_TYPE_SHARED,
        __uuidof(IDWriteFactory),
        reinterpret_cast<IUnknown**>(&writeFactory)
    );

    writeFactory->CreateTextFormat(
        L"Calibri",                // Font family name.
        NULL,                       // Font collection (NULL sets it to use the system font collection).
        DWRITE_FONT_WEIGHT_REGULAR,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        20.0f,
        L"en-us",
        &textFormat
    );

    textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
    textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

    return true;
}

bool Graphics::DrawTextOnScene(FLOAT posX, FLOAT posY, const wchar_t* wszText)
{
    if (renderTarget)
    {
        renderTarget->BeginDraw();
        renderTarget->SetTransform(D2D1::IdentityMatrix());
        configureBrush(posX, posY, wszText);

        renderTarget->EndDraw();

        return true;
    }
    return false;
}

// Configurate layout to text and brush to draw text
void Graphics::configureBrush(FLOAT posX, FLOAT posY, const wchar_t* wszText) 
{
    D2D1_RECT_F layoutRect = D2D1::RectF(
        static_cast<FLOAT>(posX),
        static_cast<FLOAT>(posY),
        static_cast<FLOAT>(0),
        static_cast<FLOAT>(0)
    );

    UINT32 cTextLength_ = (UINT32)wcslen(wszText);

    renderTarget->DrawTextW(
        wszText,   // The string to render.
        cTextLength_,    // The string's length.
        textFormat,    // The text format.
        layoutRect,       // The region of the window where the text will be rendered.
        brush    // The brush used to draw the text.
    );

}

void Graphics::initImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

#if 1
    io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;     
    io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports; 
#endif
    
    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplWin32_Init(window->GetWnd());
    ImGui_ImplDX11_Init(device, context);  
}

bool Graphics::initDepthShadowMap()
{
    std::wstring shaderPath = graphicsPath + L"Shaders/ShaderDepthTexture.fx";
    depthShader = new DepthShader(this, shaderPath.data());
    depthShader->Init();

    // Creating a texture sample (description) 
    D3D11_SAMPLER_DESC sampDesc;
    ZeroMemory(&sampDesc, sizeof(sampDesc));
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;      // Type of filtering
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;         // Setting coordinates
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

    // Creating a texturing sample interface
    auto hr = device->CreateSamplerState(&sampDesc, &shadowSamplerState);
    ErrorLogger::DirectXLog(hr, Error, "Failed create SamplerState", __FILE__, __FUNCTION__, __LINE__);

    return true;
}

void Graphics::PrepareRenderScene()
{
    context->PSSetSamplers(1, 1, &shadowSamplerState);
}

ID3D11Device* Graphics::GetDevice()
{
    return device;
}

ID3D11DeviceContext* Graphics::GetContext()
{
    return context;
}

IDXGISwapChain* Graphics::GetSwapChain()
{
    return swapChain;
}

ID3D11RenderTargetView* Graphics::GetBackBufferRenderTargetView()
{
    return backBufferRenderTargetView;
}

ID3DUserDefinedAnnotation* Graphics::GetAnnotation()
{
    return annotation;
}

ID3D11Texture2D* Graphics::GetDepthStencil()
{
    return depthStencil;
}

ID3D11DepthStencilView* Graphics::GetDepthStencilView()
{
    return depthStencilView;
}

LightShader* Graphics::GetLightShader()
{
    return lightShader;
}

ModelShader* Graphics::GetModelShader()
{
    return modelShader;
}

MeshRenderer* Graphics::GetMeshRenderer() const
{
    return meshRenderer;
}

bool Graphics::HasLight() const
{
    return hasLight;
}

bool Graphics::HasShadow() const
{
    return hasShadow;
}

void Graphics::PrepareRenderBackBuffer()
{
    context->RSSetState(rasterState);
    context->RSSetViewports(1, &viewport);
    context->OMSetRenderTargets(1, &backBufferRenderTargetView, depthStencilView);

    float color[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    context->ClearRenderTargetView(backBufferRenderTargetView, color);
    context->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Graphics::PrepareRenderShadowMap() const
{
    context->RSSetState(rasterState);

    depthShader->SetShader();
}

void Graphics::PrepareRenderSceneMap()
{
    context->RSSetState(rasterState);
    context->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

Window* Graphics::GetWindow() const
{
    return window;
}

OrthoWindow* Graphics::GetOrthoWindow() const
{
    return orthoWindow;
}

void Graphics::initShaders()
{
    std::wstring shaderPath = graphicsPath + L"Shaders/ShaderDeferredLight.fx";
    lightShader = new LightShader(this, shaderPath.data());
    lightShader->Init();

    shaderPath = graphicsPath + L"Shaders/ShaderDeferredModel.fx";
    modelShader = new ModelShader(this, shaderPath.data());
    modelShader->Init();
}
