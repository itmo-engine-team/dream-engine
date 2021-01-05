#include "Texture.h"

#include "ErrorLogger.h"
#include <WICTextureLoader.h>

#include "Graphics.h"

Texture::Texture(Graphics* graphics, const wchar_t* texturePath) : graphics(graphics)
{
    // Loading a texture from file
    auto hr = DirectX::CreateWICTextureFromFile(graphics->GetDevice(),
        texturePath, nullptr, &textureResource, 0);
    isValid = !FAILED(hr);
}

Texture::Texture(Graphics* graphics, ID3D11Texture2D* texture) : graphics(graphics)
{

    D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
    ZeroMemory(&shaderResourceViewDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
    shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    shaderResourceViewDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
    shaderResourceViewDesc.Texture2D.MipLevels = 1;

    auto hr = graphics->GetDevice()->CreateShaderResourceView(texture, &shaderResourceViewDesc, &textureResource);
    isValid = !FAILED(hr);
}

const bool Texture::IsValid() const
{
    return isValid;
}

void Texture::SetTexture(int slot)
{
    graphics->GetContext()->PSSetShaderResources(slot, 1, &textureResource);
}

ID3D11ShaderResourceView* Texture::GetShaderResourceView() const
{
    return textureResource;
}
