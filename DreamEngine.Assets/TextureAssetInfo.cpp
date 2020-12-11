#include "TextureAssetInfo.h"

TextureAssetInfo::TextureAssetInfo() : AssetInfo(AssetType::Texture)
{
}

TextureAssetInfo::TextureAssetInfo(TextureAssetInfo& assetInfo) : AssetInfo(assetInfo)
{
    texturePath = assetInfo.texturePath;
}

void TextureAssetInfo::SetTexturePath(std::string& path)
{
    texturePath = path;
}

const std::string& TextureAssetInfo::GetTexturePath()
{
    return texturePath;
}

Json TextureAssetInfo::toJson()
{
    Json json = AssetInfo::toJson();

    json["texturePath"] = texturePath;

    return json;
}

void TextureAssetInfo::fromJson(Json json)
{
    initVariable(json, "texturePath", &texturePath);
}
