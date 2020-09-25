#pragma once

#include <d3d11.h>

class Game;

class Texture
{
public:
	Texture(Game* game, const wchar_t* texturePath);

	void setTexture();

protected:
	Game* m_game;
	Graphics* graphics;

	ID3D11ShaderResourceView* g_pTextureRV = nullptr;    // Texture object
	ID3D11SamplerState* g_pSamplerLinear = nullptr;    // texture blending
};

