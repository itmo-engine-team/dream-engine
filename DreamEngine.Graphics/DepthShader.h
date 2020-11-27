#pragma once

#include "Shader.h"

class DepthShader : public Shader
{
public:

    DepthShader(Graphics* graphics, const wchar_t* shaderPath);
    virtual ~DepthShader() = default;

    void Init() override;
};

