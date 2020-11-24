#pragma once

#include <d3d11.h>

class Engine;
class Graphics;

class Texture
{
public:

    Texture(Engine* engine, const wchar_t* texturePath);
    Texture(Engine* engine, ID3D11Texture2D* texture);

    void SetTexture();

protected:

    Engine* engine;
    Graphics* graphics;

    ID3D11ShaderResourceView* textureResource = nullptr;    // Texture object
    ID3D11SamplerState* samplerState = nullptr;    // texture blending

};

