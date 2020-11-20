#include "Graphics.h"

#include "ErrorLogger.h"
#include "DepthShader.h"

Graphics::Graphics()
{

}

bool Graphics::DirectXInitialize(int screenWidth, int screenHeight, HWND hWnd)
{
    HRESULT res;

    DXGI_SWAP_CHAIN_DESC swapDesc = {};
    swapDesc.BufferCount = 1;
    swapDesc.BufferDesc.Width = screenWidth;
    swapDesc.BufferDesc.Height = screenHeight;
    swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapDesc.OutputWindow = hWnd;
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
    res = device->CreateRenderTargetView(backTex, nullptr, &renderTargetView);
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

    res = device->CreateRasterizerState(&rastDesc, &shadowRasterState);
    ErrorLogger::DirectXLog(res, Error,
        "Failed to create ShadowRasterizerState", __FILE__, __FUNCTION__, __LINE__);

    // Structure with parameters: 
    D3D11_TEXTURE2D_DESC descDepth;
    ZeroMemory(&descDepth, sizeof(descDepth));
    descDepth.Width = screenWidth;      // Width
    descDepth.Height = screenHeight;    // height of the texture
    descDepth.MipLevels = 1;            // interpolation level
    descDepth.ArraySize = 1;
    descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; // Format (pixel size)
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
    viewport.Width = screenWidth;
    viewport.Height = screenHeight;
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.MinDepth = 0;
    viewport.MaxDepth = 1.0f;

    viewports.push_back(viewport);

    initDepthShadowMap();
    initSceneMap(screenWidth, screenHeight);

    direct2DInitialize(hWnd);
    setupImGui(hWnd);
    SwitchWindow();

    return true;
}

bool Graphics::direct2DInitialize(HWND hWnd)
{
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);

    ID3D11Resource* res;
    this->renderTargetView->GetResource(&res);

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

void Graphics::setupImGui(HWND hWnd)
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

    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX11_Init(device, context);  
}

void Graphics::SwitchWindow()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    // create ImGui window
    ImGui::Begin("Switch mode");
    ImGui::SetWindowSize(ImVec2(200, 100));
    ImGui::Checkbox("Game mode", &this->gameMode);
    ImGui::Checkbox("Edit mode", &this->editMode);
    ImGui::End();

    if (editMode == true)
    {
        createShadowViewport();
        createGameViewport();
    }

    // assemble together draw data
    ImGui::Render();

    context->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

    // render draw data
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
    
    swapChain->Present(1, 0);
}

bool Graphics::initDepthShadowMap()
{
    depthShader = new DepthShader(this, L"Shaders/ShaderDepthTexture.fx");
    depthShader->Init();

    // Creating a depth buffer
    D3D11_TEXTURE2D_DESC shadowMapDesc;
    ZeroMemory(&shadowMapDesc, sizeof(D3D11_TEXTURE2D_DESC));
    shadowMapDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
    shadowMapDesc.MipLevels = 1;
    shadowMapDesc.ArraySize = 1;
    shadowMapDesc.SampleDesc.Count = 1;
    shadowMapDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_DEPTH_STENCIL;
    shadowMapDesc.Height = 1024;
    shadowMapDesc.Width = 1024;

    HRESULT hr = device->CreateTexture2D(&shadowMapDesc, nullptr, &shadowMap);

    // Creating a resource view
    D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
    ZeroMemory(&depthStencilViewDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
    depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    depthStencilViewDesc.Texture2D.MipSlice = 0;

    D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
    ZeroMemory(&shaderResourceViewDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
    shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    shaderResourceViewDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
    shaderResourceViewDesc.Texture2D.MipLevels = 1;

    hr = device->CreateDepthStencilView(shadowMap, &depthStencilViewDesc, &shadowDepthView);

    hr = device->CreateShaderResourceView(shadowMap, &shaderResourceViewDesc, &shadowResourceView);

    // Create comparisonSamplerDesc
    D3D11_SAMPLER_DESC comparisonSamplerDesc;
    ZeroMemory(&comparisonSamplerDesc, sizeof(D3D11_SAMPLER_DESC));
    comparisonSamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
    comparisonSamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
    comparisonSamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
    comparisonSamplerDesc.BorderColor[0] = 1.0f;
    comparisonSamplerDesc.BorderColor[1] = 1.0f;
    comparisonSamplerDesc.BorderColor[2] = 1.0f;
    comparisonSamplerDesc.BorderColor[3] = 1.0f;
    comparisonSamplerDesc.MinLOD = 0.f;
    comparisonSamplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
    comparisonSamplerDesc.MipLODBias = 0.f;
    comparisonSamplerDesc.MaxAnisotropy = 0;
    comparisonSamplerDesc.ComparisonFunc = D3D11_COMPARISON_LESS_EQUAL;
    comparisonSamplerDesc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT;

    // Create state of comparison
    D3D11_RASTERIZER_DESC drawingRenderStateDesc;
    ZeroMemory(&drawingRenderStateDesc, sizeof(D3D11_RASTERIZER_DESC));
    drawingRenderStateDesc.CullMode = D3D11_CULL_BACK;
    drawingRenderStateDesc.FillMode = D3D11_FILL_SOLID;
    drawingRenderStateDesc.DepthClipEnable = true;

    // Create rasterize state
    D3D11_RASTERIZER_DESC shadowRenderStateDesc;
    ZeroMemory(&shadowRenderStateDesc, sizeof(D3D11_RASTERIZER_DESC));
    shadowRenderStateDesc.CullMode = D3D11_CULL_FRONT;
    shadowRenderStateDesc.FillMode = D3D11_FILL_SOLID;
    shadowRenderStateDesc.DepthClipEnable = true;
    
    // Init viewport for shadow rendering
    shadowMapViewport = {};
    ZeroMemory(&shadowMapViewport, sizeof(D3D11_VIEWPORT));
    shadowMapViewport.Height = 600;
    shadowMapViewport.Width = 800;
    shadowMapViewport.MinDepth = 0.f;
    shadowMapViewport.MaxDepth = 1.f;

    viewports.push_back(shadowMapViewport);

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
    hr = device->CreateSamplerState(&sampDesc, &shadowSamplerState);
    ErrorLogger::DirectXLog(hr, Error, "Failed create SamplerState", __FILE__, __FUNCTION__, __LINE__);

    return true;
}

bool Graphics::initSceneMap(int screenWidth, int screenHeight)
{
    // Creating a depth buffer
    D3D11_TEXTURE2D_DESC sceneMapDesc;
    ZeroMemory(&sceneMapDesc, sizeof(D3D11_TEXTURE2D_DESC));
    sceneMapDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    sceneMapDesc.MipLevels = 1;
    sceneMapDesc.ArraySize = 1;
    sceneMapDesc.SampleDesc.Count = 1;
    sceneMapDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
    sceneMapDesc.Height = screenHeight;
    sceneMapDesc.Width = screenWidth;

    HRESULT hr = device->CreateTexture2D(&sceneMapDesc, nullptr, &sceneMap);

    D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
    renderTargetViewDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
    renderTargetViewDesc.Texture2D.MipSlice = 0;

    hr = device->CreateRenderTargetView(sceneMap, &renderTargetViewDesc, &sceneRenderTargetView);

    D3D11_SHADER_RESOURCE_VIEW_DESC sceneResourceViewDesc;
    sceneResourceViewDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    sceneResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    sceneResourceViewDesc.Texture2D.MostDetailedMip = 0;
    sceneResourceViewDesc.Texture2D.MipLevels = 1;

    hr = device->CreateShaderResourceView(sceneMap, &sceneResourceViewDesc, &sceneResourceView);

    return true;
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

ID3D11RenderTargetView* Graphics::GetRenderTargetView()
{
    return renderTargetView;
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

ID3D11Texture2D* Graphics::GetShadowMap()
{
    return shadowMap;
}

bool Graphics::GetGameMode()
{
    return gameMode;
}

void Graphics::createShadowViewport()
{
    ImGui::Begin("ShadowRender");
    ImGui::Image(shadowResourceView, ImVec2(300, 300));
    ImGui::End();
}

void Graphics::createGameViewport()
{
    ImGui::Begin("GameViewport");
    ImGui::Image(sceneResourceView, ImVec2(400, 300));
    ImGui::End();
}

void Graphics::PrepareRenderScene()
{
    context->RSSetState(rasterState);
    context->RSSetViewports(1, &viewport);
    context->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

    context->PSSetShaderResources(1, 1, &shadowResourceView);
    context->PSSetSamplers(1, 1, &shadowSamplerState);
}

void Graphics::PrepareRenderShadowMap()
{
    context->RSSetState(shadowRasterState);
    context->OMSetRenderTargets(0, nullptr, shadowDepthView);
    context->ClearDepthStencilView(shadowDepthView, D3D11_CLEAR_DEPTH, 1.0f, 0);

    depthShader->SetShader();
}

void Graphics::PrepareRenderSceneMap(int screenWidth, int screenHeight)
{
    context->ClearState();

    context->OMSetRenderTargets(1, &sceneRenderTargetView, depthStencilView);

    //TODO: move shadows
    context->PSSetShaderResources(1, 1, &shadowResourceView); 
    context->PSSetSamplers(1, 1, &shadowSamplerState);

    D3D11_VIEWPORT viewport = {};
    viewport.Width = static_cast<float>(screenWidth);
    viewport.Height = static_cast<float>(screenHeight);
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.MinDepth = 0;
    viewport.MaxDepth = 1.0f;
    
    context->RSSetViewports(1, &viewport);
    context->RSSetState(rasterState);

    float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

    context->ClearRenderTargetView(sceneRenderTargetView, clearColor);
    context->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}
