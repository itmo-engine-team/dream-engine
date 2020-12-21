#pragma once

#include "AssetInfo.h"

class SceneAssetInfo : public AssetInfo
{

public:

    SceneAssetInfo();
    SceneAssetInfo(SceneAssetInfo& assetInfo);

protected:

    Json toJson() override;
    void fromJson(Json json) override;

};

class SceneAssetInfoCreator : public AssetInfoCreator
{

    AssetInfo* Create() override
    {
        return new SceneAssetInfo();
    }

    AssetInfo* Duplicate(AssetInfo& assetInfo) override
    {
        return new SceneAssetInfo(dynamic_cast<SceneAssetInfo&>(assetInfo));
    }

};