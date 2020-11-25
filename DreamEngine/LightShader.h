#pragma once

#include <d3d11.h>

#include "Shader.h"

class DeferredBuffers;

class LightShader : public Shader
{

public:

    LightShader(Graphics* graphics, const wchar_t* shaderPath);
    ~LightShader() = default;

    void Init() override;

    void SetShader(DeferredBuffers* deferredBuffers);

private:

    ID3D11SamplerState* samplerState = nullptr;

};
