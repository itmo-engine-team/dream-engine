#include "Graphics.h"
#include "Game.h"

Graphics::Graphics(Game* currentGame)
{
	game = currentGame;
}

bool Graphics::DirectXInitialize()
{
	HRESULT res;

	DXGI_SWAP_CHAIN_DESC swapDesc = {};
	swapDesc.BufferCount = 1;
	swapDesc.BufferDesc.Width = game->screenWidth;
	swapDesc.BufferDesc.Height = game->screenHeight;
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.OutputWindow = game->hWnd;
	swapDesc.Windowed = true;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapDesc.Flags = 0;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;

	D3D_FEATURE_LEVEL featureLevel[] = { D3D_FEATURE_LEVEL_11_1 };
	res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
		D3D11_CREATE_DEVICE_DEBUG, featureLevel, 1, D3D11_SDK_VERSION,
		&swapDesc, &game->swapChain, &game->device, nullptr, &game->context);
	ZCHECK(res);

	ID3D11Texture2D* backTex;
	res = game->swapChain->GetBuffer(0, IID_ID3D11Texture2D, (void**)&backTex);
	ZCHECK(res);
	res = game->device->CreateRenderTargetView(backTex, nullptr, &game->rtv);
	ZCHECK(res);

	game->context->QueryInterface(IID_ID3DUserDefinedAnnotation, (void**)&game->annotation);

	ID3D11Debug* debug;
	game->device->QueryInterface(IID_ID3D11Debug, (void**)&debug);

	CD3D11_RASTERIZER_DESC rastDesc = {};
	rastDesc.CullMode = D3D11_CULL_NONE;
	rastDesc.FillMode = D3D11_FILL_SOLID;

	ID3D11RasterizerState* rastState;
	res = game->device->CreateRasterizerState(&rastDesc, &rastState); ZCHECK(res);

	game->context->RSSetState(rastState);

	D3D11_TEXTURE2D_DESC descDepth;           // Структура с параметрами
	ZeroMemory(&descDepth, sizeof(descDepth));
	descDepth.Width = game->screenWidth;      // ширина и
	descDepth.Height = game->screenHeight;    // высота текстуры
	descDepth.MipLevels = 1;                  // уровень интерполяции
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; // формат (размер пикселя)
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;         // вид - буфер глубин
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;

	// При помощи заполненной структуры-описания создаем объект текстуры
	game->device->CreateTexture2D(&descDepth, NULL, &game->depthStencil);

	// Теперь надо создать сам объект буфера глубин
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;            // Структура с параметрами
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;               // формат как в текстуре
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	// При помощи заполненной структуры-описания и текстуры создаем объект буфера глубин
	game->device->CreateDepthStencilView(game->depthStencil, &descDSV, &game->depthStencilView);


	D3D11_VIEWPORT viewport = {};
	viewport.Width = game->screenWidth;
	viewport.Height = game->screenHeight;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1.0f;

	game->context->RSSetViewports(1, &viewport);
	game->context->OMSetRenderTargets(1, &game->rtv, game->depthStencilView);


    return false;
}
