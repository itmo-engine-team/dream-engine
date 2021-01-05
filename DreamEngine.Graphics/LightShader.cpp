#include "LightShader.h"

#include <d3dcompiler.h>

#include "Graphics.h"
#include "DeferredBuffers.h"
#include "ErrorLogger.h"

LightShader::LightShader(Graphics* graphics, const wchar_t* shaderPath)
    : Shader(graphics, shaderPath)
{
}

void LightShader::Init()
{
    // Creating a texture sample(description)
    D3D11_SAMPLER_DESC sampDesc;
    ZeroMemory(&sampDesc, sizeof(sampDesc));
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;      // Type of filtering
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;         // Setting coordinates
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

    // Creating a texturing sample interface
    auto hr = graphics->GetDevice()->CreateSamplerState(&sampDesc, &samplerState);
    ErrorLogger::DirectXLog(hr, Error, "Failed create SamplerState", __FILE__, __FUNCTION__, __LINE__);

    D3D11_INPUT_ELEMENT_DESC polygonLayout[2];

    // Create the vertex input layout description.
    polygonLayout[0].SemanticName = "POSITION";
    polygonLayout[0].SemanticIndex = 0;
    polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
    polygonLayout[0].InputSlot = 0;
    polygonLayout[0].AlignedByteOffset = 0;
    polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    polygonLayout[0].InstanceDataStepRate = 0;

    polygonLayout[1].SemanticName = "TEXCOORD";
    polygonLayout[1].SemanticIndex = 0;
    polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
    polygonLayout[1].InputSlot = 0;
    polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
    polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    polygonLayout[1].InstanceDataStepRate = 0;

    // Get a count of the elements in the layout.
    const int numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);
    initInternal(polygonLayout, numElements);
}

void LightShader::SetShader(DeferredBuffers* deferredBuffers)
{
    Shader::SetShader();

    graphics->GetContext()->PSSetShaderResources(0, DeferredBuffers::BUFFER_COUNT,
        deferredBuffers->GetShaderResourceViewArray());
    graphics->GetContext()->PSSetSamplers(0, 1, &samplerState);
}
