#include "Window.h"
#include "Game.h"

Window::Window(Game* currentGame)
{
	game = currentGame;
}

bool Window::WindowInitialize(HINSTANCE hInstance, WNDCLASSEX wc)
{
	LPCWSTR applicationName;

	DEVMODE dmScreenSettings;
	int posX, posY;

	// Give the application a name.
	applicationName = L"Game";

	// Setup the windows class with default settings.
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the window class.
	RegisterClassEx(&wc);

	// Determine the resolution of the clients desktop screen.
	game->screenWidth = GetSystemMetrics(SM_CXSCREEN);
	game->screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// If windowed then set it to 800x800 resolution.
	game->screenWidth = 1200;
	game->screenHeight = 800;

	// Place the window in the middle of the screen.
	posX = (GetSystemMetrics(SM_CXSCREEN) - game->screenWidth) / 2;
	posY = (GetSystemMetrics(SM_CYSCREEN) - game->screenHeight) / 2;

	RECT windowRect = { 0, 0,
		static_cast<LONG>(game->screenWidth), static_cast<LONG>(game->screenHeight) };
	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);


	auto dwStyle = WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_THICKFRAME; // WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP
	// Create the window with the screen settings and get the handle to it.
	game->hWnd = CreateWindowEx(WS_EX_APPWINDOW, applicationName, applicationName,
		dwStyle,
		posX, posY,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		nullptr, nullptr, hInstance, nullptr);

	static bool raw_input_initialized = false;
	if (raw_input_initialized == false)
	{
		RAWINPUTDEVICE rid;

		rid.usUsagePage = 0x01; //Mouse
		rid.usUsage = 0x02;
		rid.dwFlags = 0;
		rid.hwndTarget = NULL;

		if (RegisterRawInputDevices(&rid, 1, sizeof(rid)) == FALSE)
		{
			std::cout << "Failed to register raw input devices.\n";
			exit(-1);
		}

		raw_input_initialized = true;
	}


	ShowWindow(game->hWnd, SW_SHOW);
	SetForegroundWindow(game->hWnd);
	SetFocus(game->hWnd);

	ShowCursor(false);
}
