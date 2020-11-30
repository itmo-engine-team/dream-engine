#pragma once

#include <d3d11_1.h>

class Graphics;

class TextureSampler
{

public:

    TextureSampler(Graphics* graphics);
    TextureSampler(Graphics* graphics, D3D11_SAMPLER_DESC desc);

    void SetSampler(int slot = 0);

private:

    Graphics* graphics;

    ID3D11SamplerState* samplerState = nullptr;

};

