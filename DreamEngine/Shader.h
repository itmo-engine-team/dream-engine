#pragma once

#include <d3d11.h>
#include <string>

class Graphics;

class Shader
{
public:

    Shader(Graphics* graphics, const wchar_t* shaderPath);
    virtual ~Shader() = default;

    virtual void Init();

    virtual void SetShader();

protected:

    Graphics* graphics = nullptr;

    std::wstring shaderPath = nullptr;

    ID3D11InputLayout* inputLayout = nullptr;
    ID3D11VertexShader* vertexShader = nullptr;
    ID3D11PixelShader* pixelShader = nullptr;

    void initInternal(D3D11_INPUT_ELEMENT_DESC* inputElements, int elementsCount);

};

