#include "DepthShader.h"

DepthShader::DepthShader(Graphics* graphics, const wchar_t* shaderPath)
    : Shader(graphics, shaderPath)
{
}

void DepthShader::Init()
{
    D3D11_INPUT_ELEMENT_DESC inputElements[] = {
        {
            "POSITION",
            0,
            DXGI_FORMAT_R32G32B32_FLOAT,
            0,
            0,
            D3D11_INPUT_PER_VERTEX_DATA,
            0
        }
    };

    initInternal(inputElements, 3);
}
