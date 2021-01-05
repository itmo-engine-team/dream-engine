#pragma once

#include "Shader.h"
#include "TextureSampler.h"

class Texture;

class ModelShader : public Shader
{
public:

    ModelShader(Graphics* graphics, const wchar_t* shaderPath);

    void Init() override;

    void SetShader() override;

protected:

    TextureSampler* sampler = nullptr;

};

