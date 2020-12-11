#pragma once

#include "AssetInfo.h"

class TextureAssetInfo : public AssetInfo
{

public:

    TextureAssetInfo();
    TextureAssetInfo(TextureAssetInfo& assetInfo);

    void SetTexturePath(std::string& path);
    const std::string& GetTexturePath();

protected:

    Json toJson() override;
    void fromJson(Json json) override;

private:

    std::string texturePath;

};

class TextureAssetInfoCreator : public AssetInfoCreator
{

    AssetInfo* Create() override
    {
        return new TextureAssetInfo();
    }

    AssetInfo* Duplicate(AssetInfo& assetInfo) override
    {
        return new TextureAssetInfo(dynamic_cast<TextureAssetInfo&>(assetInfo));
    }

};