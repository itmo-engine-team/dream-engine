#include "TextureSampler.h"

#include "ErrorLogger.h"
#include "Graphics.h"

TextureSampler::TextureSampler(Graphics* graphics) : graphics(graphics)
{
    // Creating a texture sample (description) 
    D3D11_SAMPLER_DESC sampDesc;
    ZeroMemory(&sampDesc, sizeof(sampDesc));
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;      // Type of filtering
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;         // Setting coordinates
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

    // Creating sampler interface
    auto hr = graphics->GetDevice()->CreateSamplerState(&sampDesc, &samplerState);
    ErrorLogger::DirectXLog(hr, Error, "Failed create SamplerState", __FILE__, __FUNCTION__, __LINE__);
}

TextureSampler::TextureSampler(Graphics* graphics, D3D11_SAMPLER_DESC desc) : graphics(graphics)
{
    // Creating sampler interface
    auto hr = graphics->GetDevice()->CreateSamplerState(&desc, &samplerState);
    ErrorLogger::DirectXLog(hr, Error, "Failed create SamplerState", __FILE__, __FUNCTION__, __LINE__);
}

void TextureSampler::SetSampler(int slot)
{
    graphics->GetContext()->PSSetSamplers(slot, 1, &samplerState);
}
