#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include <iostream>
#include "winuser.h"
#include <wrl.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

#include <d3d.h>
#include <d3d11.h>
#include <d3d11_1.h>
#include <directxmath.h>
#include "Engine/Game.h"
#include "KatamariGame.h"

#define ZCHECK(exp) if(FAILED(exp)) { printf("Check failed at file: %s at line %i", __FILE__, __LINE__); return 0; }

using namespace Microsoft::WRL;
using namespace DirectX;

Game* game;

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
		// Check if the window is being destroyed.
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}

	// Check if the window is being closed.
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}

	case WM_SIZE:
	{
		std::cout << "Width " << LOWORD(lparam) << " Height " << HIWORD(lparam) << std::endl;

		return 0;
	}

	case WM_PAINT:
	{
		// Calculate current time and delta time	
		static float t = 0.0f;
		static DWORD dwTimeStart = GetTickCount();
		DWORD dwTimeCur = GetTickCount();
		t = (dwTimeCur - dwTimeStart) / 1000.0f;
		game->deltaTime = t - game->currentTime;
		game->currentTime = t;

		//std::cout << "Time " << game->deltaTime << "\n";

		game->doFrame();

		return 0;
	}

	// Input Device
	case WM_KILLFOCUS:
		game->inputDevice->ClearState();
		break;
	case WM_SYSKEYDOWN:
	case WM_KEYDOWN:
		if (!(lparam & 0x40000000) || game->inputDevice->AutorepeatIsEnabled())
		{
			game->inputDevice->OnKeyPressed(static_cast<unsigned char>(wparam));
		}
		game->inputDevice->OnKeyPressed(static_cast<unsigned char>(wparam));

		// If a key is pressed send it to the input object so it can record that state.
		//std::cout << "Key: " << (unsigned int)wparam << std::endl;

		if ((unsigned int)wparam == 27) PostQuitMessage(0);
		break;
	case WM_SYSKEYUP:
	case WM_KEYUP:
		game->inputDevice->OnKeyReleased(static_cast<unsigned char>(wparam));
		break;
	case WM_CHAR:
		game->inputDevice->OnChar(static_cast<unsigned char>(wparam));
		break;
		//End Input Device

	case WM_LBUTTONDOWN:
	{
		break;
	}
	case WM_MOUSEMOVE:
	{
		int x = LOWORD(lparam);
		int y = HIWORD(lparam);
		game->mouse->OnMouseMove(x, y);
		break;
	}

	case WM_INPUT:
	{
		UINT dataSize;
		GetRawInputData(reinterpret_cast<HRAWINPUT>(lparam), RID_INPUT, NULL, &dataSize, sizeof(RAWINPUTHEADER)); //Need to populate data size first

		if (dataSize > 0)
		{
			std::unique_ptr<BYTE[]> rawdata = std::make_unique<BYTE[]>(dataSize);
			if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lparam), RID_INPUT, rawdata.get(), &dataSize, sizeof(RAWINPUTHEADER)) == dataSize)
			{
				RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(rawdata.get());
				if (raw->header.dwType == RIM_TYPEMOUSE)
				{
					game->mouse->OnRawDelta(raw->data.mouse.lLastX, raw->data.mouse.lLastY);
				}
			}
		}

		return DefWindowProc(hwnd, umessage, wparam, lparam); //Need to call DefWindowProc for WM_INPUT messages
	}

	// All other messages pass to the message handler in the system class.
	default:
	{
		return DefWindowProc(hwnd, umessage, wparam, lparam);
	}
	}
}

int WINAPI main(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	WNDCLASSEX wc;
	wc.lpfnWndProc = WndProc;
	game = new KatamariGame(hInstance, wc);
	
#pragma region DirectX initialization
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

	D3D11_TEXTURE2D_DESC descDepth;     // Структура с параметрами
	ZeroMemory(&descDepth, sizeof(descDepth));
	descDepth.Width = game->screenWidth;            // ширина и
	descDepth.Height = game->screenHeight;    // высота текстуры
	descDepth.MipLevels = 1;            // уровень интерполяции
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
	descDSV.Format = descDepth.Format;         // формат как в текстуре
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

#pragma endregion DirectX initialization

	MSG msg = {};

	game->init();

	// Loop until there is a quit message from the window or the user.
	bool isExitRequested = false;
	while (!isExitRequested) {
		// Handle the windows messages.
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// If windows signals to end the application then exit out.
		if (msg.message == WM_QUIT) {
			isExitRequested = true;
		}
	}

	debug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);

	return 0;
}
