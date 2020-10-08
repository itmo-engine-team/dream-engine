#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include <iostream>
#include "winuser.h"
#include <wrl.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

#include <directxmath.h>
#include "Engine.h"

using namespace Microsoft::WRL;
using namespace DirectX;

Engine* engine;

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
        engine->DoFrame();
        return 0;
    }

    // Input Device
    case WM_KILLFOCUS:
        engine->GetInputDevice()->ClearState();
        break;
    case WM_SYSKEYDOWN:
    case WM_KEYDOWN:
        if (!(lparam & 0x40000000) || engine->GetInputDevice()->AutorepeatIsEnabled())
        {
            engine->GetInputDevice()->OnKeyPressed(static_cast<unsigned char>(wparam));
        }
        engine->GetInputDevice()->OnKeyPressed(static_cast<unsigned char>(wparam));

        // If a key is pressed send it to the input object so it can record that state.
        //std::cout << "Key: " << (unsigned int)wparam << std::endl;

        if ((unsigned int)wparam == 27) PostQuitMessage(0);
        break;
    case WM_SYSKEYUP:
    case WM_KEYUP:
        engine->GetInputDevice()->OnKeyReleased(static_cast<unsigned char>(wparam));
        break;
    case WM_CHAR:
        engine->GetInputDevice()->OnChar(static_cast<unsigned char>(wparam));
        break;
        //End Input Device

    case WM_LBUTTONDOWN:
    {
        break;
    }
    case WM_MOUSEMOVE:
    {
        const int x = LOWORD(lparam);
        const int y = HIWORD(lparam);
        engine->GetMouse()->OnMouseMove(x, y);
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
                    engine->GetMouse()->OnRawDelta(raw->data.mouse.lLastX, raw->data.mouse.lLastY);
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

    engine = new Engine(hInstance, wc);

    MSG msg = {};

    // Loop until there is a quit message from the window or the user.
    bool isExitRequested = false;
    while (!isExitRequested) 
    {
        // Handle the windows messages.
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) 
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // If windows signals to end the application then exit out.
        if (msg.message == WM_QUIT) 
        {
            isExitRequested = true;
        }
    }

    //debug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);

    return 0;
}
