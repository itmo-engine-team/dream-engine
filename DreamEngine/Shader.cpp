#include "Shader.h"

#include "Graphics.h"

#include <d3dcompiler.h>

#include "ErrorLogger.h"

Shader::Shader(Graphics* graphics, const wchar_t* shaderPath)
    : graphics(graphics), shaderPath(std::wstring(shaderPath))
{
}

void Shader::SetShader()
{
    graphics->GetContext()->PSSetShader(pixelShader, nullptr, 0u);
    graphics->GetContext()->VSSetShader(vertexShader, nullptr, 0u);
    graphics->GetContext()->IASetInputLayout(inputLayout);
}

void Shader::Init()
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
        }
    };

    initInternal(inputElements, 3);
}

void Shader::initInternal(D3D11_INPUT_ELEMENT_DESC* inputElements, const int elementsCount)
{
    ID3D11Device* device = graphics->GetDevice();

    // Compile vertex shader
    ID3DBlob* vertexBC = nullptr;
    ID3DBlob* errorVertexCode = nullptr;
    auto hr = D3DCompileFromFile(shaderPath.c_str(),
        nullptr /*macros*/,
        nullptr /*include*/,
        "VSMain",
        "vs_5_0",
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION | D3DCOMPILE_PACK_MATRIX_ROW_MAJOR,
        0,
        &vertexBC,
        &errorVertexCode);

    if (FAILED(hr)) {
        // If the shader failed to compile it should have written something to the error message.
        if (errorVertexCode) {
            char* compileErrors = (char*)(errorVertexCode->GetBufferPointer());
            ErrorLogger::DirectXLog(hr, Error, compileErrors, __FILE__, __FUNCTION__, __LINE__);
        }
        // If there was nothing in the error message then it simply could not find the shader file itself.
        else
        {
            ErrorLogger::DirectXLog(hr, Error, "Missing Shader file", __FILE__, __FUNCTION__, __LINE__);
        }
        return;
    }

    // Create vertex shader
    device->CreateVertexShader(
        vertexBC->GetBufferPointer(),
        vertexBC->GetBufferSize(),
        nullptr,
        &vertexShader
        );

    // Do not delete - Saved to not forget that shader can be modified with macros
    // D3D_SHADER_MACRO Shader_Macros[] = { "TEST", "1", "TCOLOR", "float4(0.0f, 1.0f, 0.0f, 1.0f)", nullptr, nullptr };

    // Compile pixel shader
    ID3DBlob* pixelBC = nullptr;
    ID3DBlob* errorPixelCode = nullptr;
    hr = D3DCompileFromFile(shaderPath.c_str(),
        nullptr/*Shader_Macros /*macros*/, nullptr /*include*/,
        "PSMain", "ps_5_0",
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION | D3DCOMPILE_PACK_MATRIX_ROW_MAJOR,
        0, &pixelBC, &errorPixelCode);

    if (FAILED(hr)) {
        // If the shader failed to compile it should have written something to the error message.
        if (errorPixelCode) {
            char* compileErrors = (char*)(errorPixelCode->GetBufferPointer());
            ErrorLogger::DirectXLog(hr, Error, compileErrors, __FILE__, __FUNCTION__, __LINE__);
        }
        // If there was  nothing in the error message then it simply could not find the shader file itself.
        else
        {
            ErrorLogger::DirectXLog(hr, Error, "Missing Shader file", __FILE__, __FUNCTION__, __LINE__);
        }
        return;
    }

    // Create vertex shader
    hr = device->CreatePixelShader(
        pixelBC->GetBufferPointer(),
        pixelBC->GetBufferSize(),
        nullptr,
        &pixelShader
        );
    ErrorLogger::DirectXLog(hr, Error, "Failed to create PixelShader", __FILE__, __FUNCTION__, __LINE__);

    // Create input layout
    ID3D11InputLayout* layout;
    hr = device->CreateInputLayout(
        inputElements,
        elementsCount,
        vertexBC->GetBufferPointer(),
        vertexBC->GetBufferSize(),
        &inputLayout);
    ErrorLogger::DirectXLog(hr, Error, "Failed to create InputLayout", __FILE__, __FUNCTION__, __LINE__);
}
