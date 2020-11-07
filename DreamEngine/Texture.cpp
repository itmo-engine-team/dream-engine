#include "Engine.h"

#include "Texture.h"
#include "ErrorLogger.h"
#include <WICTextureLoader.h>

Texture::Texture(Engine* engine, const wchar_t* texturePath) : engine(engine)
{
    graphics = engine->GetGraphics();

    // Loading a texture from file
    auto hr = DirectX::CreateWICTextureFromFile(graphics->GetDevice(), texturePath, nullptr, &textureResource, 0);

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
    hr = graphics->GetDevice()->CreateSamplerState(&sampDesc, &samplerState);
    ErrorLogger::DirectXLog(hr, Error, "Failed create SamplerState", __FILE__, __FUNCTION__, __LINE__);

}

Texture::Texture(Engine* engine, ID3D11Texture2D* texture)
{
    graphics = engine->GetGraphics();

    D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
    ZeroMemory(&shaderResourceViewDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
    shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    shaderResourceViewDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
    shaderResourceViewDesc.Texture2D.MipLevels = 1;

    auto hr = graphics->GetDevice()->CreateShaderResourceView(texture, &shaderResourceViewDesc, &textureResource);

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
    hr = graphics->GetDevice()->CreateSamplerState(&sampDesc, &samplerState);
    ErrorLogger::DirectXLog(hr, Error, "Failed create SamplerState", __FILE__, __FUNCTION__, __LINE__);
}

void Texture::setTexture()
{
    graphics->GetContext()->PSSetShaderResources(0, 1, &textureResource);
    graphics->GetContext()->PSSetSamplers(0, 1, &samplerState);
}
