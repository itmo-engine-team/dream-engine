#pragma once

#include <d3d11.h>

class Graphics;

class Texture
{
public:

    Texture(Graphics* graphics, const wchar_t* texturePath);
    Texture(Graphics* graphics, ID3D11Texture2D* texture);

    void SetTexture();

protected:

    Graphics* graphics;

    ID3D11ShaderResourceView* textureResource = nullptr;    // Texture object
    ID3D11SamplerState* samplerState = nullptr;    // texture blending

};

