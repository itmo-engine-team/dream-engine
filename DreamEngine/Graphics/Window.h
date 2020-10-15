#pragma once

#include <d3d.h>

class Engine;

class Window
{
public:

    Window(Engine* engine);

    bool WindowInitialize(HINSTANCE hInstance, WNDCLASSEX wc);

    HWND GetWnd() const;

private:

    Engine* engine;

    HWND hWnd;

};

