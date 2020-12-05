#define WIN32_LEAN_AND_MEAN

#include "windows.h"
#include <iostream>
#include "winuser.h"
#include <wrl.h>

#include "Engine.h"
#include "PongGame.h"

using namespace Microsoft::WRL;

Engine* engine;
InputSystem* inputSystem;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);
LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
    if (ImGui_ImplWin32_WndProcHandler(hwnd, umessage, wparam, lparam)) 
    {
        return true;
    }

    if (engine->ProcessWndMessage(hwnd, umessage, wparam, lparam))
    {
        return true;
    }

    inputSystem->ProcessWndMessage(hwnd, umessage, wparam, lparam);
      
    switch (umessage)
    {
        // Check if the window is being destroyed.
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        // Check if the window is being closed.
        case WM_CLOSE:
            PostQuitMessage(0);
            return 0;
        case WM_SIZE:
            std::cout << "Width " << LOWORD(lparam) << " Height " << HIWORD(lparam) << std::endl;
            return 0;
        case WM_KEYDOWN:
            if (wparam == 27) PostQuitMessage(0);
            break;

        // All other messages pass to the message handler in the system class.
        default:
            return DefWindowProc(hwnd, umessage, wparam, lparam);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
    PSTR cmdLine, int showCmd)
{
    WNDCLASSEX wc;
    wc.lpfnWndProc = WndProc;

    inputSystem = new InputSystem();

    engine = new Engine(new PongGame(), inputSystem, hInstance, wc);
    engine->Init();

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
