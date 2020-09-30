#include "Engine.h"
#include "Texture.h"
#include "..//ErrorLogger/ErrorLogger.h"
#include <WICTextureLoader.h>

Texture::Texture(Engine* engine, const wchar_t* texturePath) : engine(engine)
{
    graphics = engine->GetGraphics();

    // Loading a texture from file
    auto hr = DirectX::CreateWICTextureFromFile(graphics->GetDevice(), texturePath, nullptr, &g_pTextureRV, 0);

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

    // Creating a texturing sample interface
    hr = graphics->GetDevice()->CreateSamplerState(&sampDesc, &g_pSamplerLinear);
    ErrorLogger::DirectXLog(hr, Error, "Failed create SamplerState", __FILE__, __FUNCTION__, __LINE__);

}

void Texture::setTexture()
{
    graphics->GetContext()->PSSetShaderResources(0, 1, &g_pTextureRV);
    graphics->GetContext()->PSSetSamplers(0, 1, &g_pSamplerLinear);
}
