#include "ModelShader.h"

#include "Texture.h"

ModelShader::ModelShader(Graphics* graphics,
                               const wchar_t* shaderPath,
                               Texture* texture)
    : Shader(graphics, shaderPath), texture(texture)
{
    hasTexture = texture != nullptr;
}

void ModelShader::SetShader()
{
    Shader::SetShader();

    if (texture != nullptr)
        texture->SetTexture();
}

bool ModelShader::HasTexture() const
{
    return hasTexture;
}

void ModelShader::Init()
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
        },
        {
            "COLOR",
            0,
            DXGI_FORMAT_R32G32B32A32_FLOAT,
            0,
            D3D11_APPEND_ALIGNED_ELEMENT,
            D3D11_INPUT_PER_VERTEX_DATA,
            0
        },
        {
            "NORMAL",
            0,
            DXGI_FORMAT_R32G32B32_FLOAT,
            0,
            D3D11_APPEND_ALIGNED_ELEMENT,
            D3D11_INPUT_PER_VERTEX_DATA,
            0
        },
        {
            "TEXCOORD",
            0,
            DXGI_FORMAT_R32G32_FLOAT,
            0,
            D3D11_APPEND_ALIGNED_ELEMENT,
            D3D11_INPUT_PER_VERTEX_DATA,
            0
        }
    };

    initInternal(inputElements, 4);
}
