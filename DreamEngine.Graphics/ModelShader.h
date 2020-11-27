#pragma once

#include "Shader.h"

class Texture;

class ModelShader : public Shader
{
public:

    ModelShader(Graphics* graphics, const wchar_t* shaderPath, Texture* texture);

    void Init() override;

    void SetShader() override;
    bool HasTexture() const;

protected:

    Texture* texture = nullptr;
    bool hasTexture;

};

