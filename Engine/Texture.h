#pragma once

#include <d3d11.h>

class Engine;

class Texture
{
public:

    Texture(Engine* engine, const wchar_t* texturePath);

    void setTexture();

protected:

    Engine* engine;
    Graphics* graphics;

    ID3D11ShaderResourceView* g_pTextureRV = nullptr;    // Texture object
    ID3D11SamplerState* g_pSamplerLinear = nullptr;    // texture blending

};

