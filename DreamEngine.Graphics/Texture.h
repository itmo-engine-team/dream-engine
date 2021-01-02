#pragma once

#include <d3d11.h>

class Graphics;

class Texture
{
public:

    Texture(Graphics* graphics, const wchar_t* texturePath);
    Texture(Graphics* graphics, ID3D11Texture2D* texture);

    const bool IsValid() const;

    void SetTexture(int slot = 0);
    ID3D11ShaderResourceView* GetShaderResourceView() const;

protected:

    bool isValid;

    Graphics* graphics;
    ID3D11ShaderResourceView* textureResource = nullptr;
};

