#pragma once
#include <d3d.h>
#include <d3d11.h>
#include <iostream>

#define ZCHECK(exp) if(FAILED(exp)) { printf("Check failed at file: %s at line %i", __FILE__, __LINE__); return 0; }

class Game;

class Graphics
{
public:
    Graphics(Game* currentGame);
    bool DirectXInitialize();
private:
    Game* game;
};

