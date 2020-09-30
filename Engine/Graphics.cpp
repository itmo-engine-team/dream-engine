#include "Graphics.h"
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
    ZCHECK(res);

    ID3D11Texture2D* backTex;
    res = swapChain->GetBuffer(0, IID_ID3D11Texture2D, (void**)&backTex);
    ZCHECK(res);
    res = device->CreateRenderTargetView(backTex, nullptr, &renderTargetView);
    ZCHECK(res);

    context->QueryInterface(IID_ID3DUserDefinedAnnotation, (void**)&annotation);

    ID3D11Debug* debug;
    device->QueryInterface(IID_ID3D11Debug, (void**)&debug);

    CD3D11_RASTERIZER_DESC rastDesc = {};
    rastDesc.CullMode = D3D11_CULL_NONE;
    rastDesc.FillMode = D3D11_FILL_SOLID;

    ID3D11RasterizerState* rastState;
    res = device->CreateRasterizerState(&rastDesc, &rastState); ZCHECK(res);

    context->RSSetState(rastState);

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
    descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;     // view - depth buffer
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

    D3D11_VIEWPORT viewport = {};
    viewport.Width = screenWidth;
    viewport.Height = screenHeight;
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.MinDepth = 0;
    viewport.MaxDepth = 1.0f;

    context->RSSetViewports(1, &viewport);
    context->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

    Direct2DInitialize(hWnd);

    return true;
}

bool Graphics::Direct2DInitialize(HWND hWnd)
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
        ConfigureBrush(posX, posY, wszText);

        renderTarget->EndDraw();

        return true;
    }
    return false;
}

// Configurate layout to text and brush to draw text
void Graphics::ConfigureBrush(FLOAT posX, FLOAT posY, const wchar_t* wszText) 
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
