#pragma once
#include <d3d.h>
#include <d3d11.h>
#include <iostream>

class Game;

class Window
{
public:
    Window(Game* currentGame);
    bool WindowInitialize(HINSTANCE hInstance, WNDCLASSEX wc);
private:
    Game* game;
};

