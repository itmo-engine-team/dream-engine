#pragma once

#include <d3d.h>

class Window
{
public:

    Window(int screenWidth, int screenHeight);

    bool WindowInitialize(HINSTANCE hInstance, WNDCLASSEX wc);

    HWND GetWnd() const;

    int GetScreenWidth() const;
    int GetScreenHeight() const;

private:

    HWND hWnd;

    int screenWidth = 0;
    int screenHeight = 0;

};

