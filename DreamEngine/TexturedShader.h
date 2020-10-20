#pragma once

#include "Shader.h"

class Texture;

class TexturedShader :
    public Shader
{
public:

    TexturedShader(Graphics* graphics, const wchar_t* shaderPath, Texture* texture);

    void Init() override;

    void SetShader() override;

protected:

    Texture* texture = nullptr;

};

