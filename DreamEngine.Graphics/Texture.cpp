#include "Texture.h"

#include "ErrorLogger.h"
#include <WICTextureLoader.h>

#include "Graphics.h"

Texture::Texture(Graphics* graphics, const wchar_t* texturePath) : graphics(graphics)
{
    // Loading a texture from file
    auto hr = DirectX::CreateWICTextureFromFile(graphics->GetDevice(),
        texturePath, nullptr, &textureResource, 0);

    // Creating a texture sample (description) 
    /*D3D11_SAMPLER_DESC sampDesc;
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
    ErrorLogger::DirectXLog(hr, Error, "Failed create SamplerState",
        __FILE__, __FUNCTION__, __LINE__);
    */
}

Texture::Texture(Graphics* graphics, ID3D11Texture2D* texture) : graphics(graphics)
{

    D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
    ZeroMemory(&shaderResourceViewDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
    shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    shaderResourceViewDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
    shaderResourceViewDesc.Texture2D.MipLevels = 1;

    auto hr = graphics->GetDevice()->CreateShaderResourceView(texture, &shaderResourceViewDesc, &textureResource);

    // Creating a texture sample (description) 
    /*D3D11_SAMPLER_DESC sampDesc;
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
    */
}

void Texture::SetTexture(int slot)
{
    graphics->GetContext()->PSSetShaderResources(slot, 1, &textureResource);
}

ID3D11ShaderResourceView* Texture::GetShaderResourceView() const
{
    return textureResource;
}
