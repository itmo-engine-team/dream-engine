#define WIN32_LEAN_AND_MEAN

#include "windows.h"
#include "winuser.h"
#include <wrl.h>

#include "Engine.h"

using namespace Microsoft::WRL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
    PSTR cmdLine, int showCmd)
{
    Engine* engine = new Engine();

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
