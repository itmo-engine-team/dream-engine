#pragma once

#include "AssetInfo.h"

class BTAssetInfo : public AssetInfo
{

public:

    BTAssetInfo();
    BTAssetInfo(BTAssetInfo& assetInfo);
    ~BTAssetInfo();

protected:

    Json toJson() override;
    void fromJson(Json json) override;

};

class BTAssetInfoCreator : public AssetInfoCreator
{

    AssetInfo* Create() override
    {
        return new BTAssetInfo();
    }

    AssetInfo* Duplicate(AssetInfo& assetInfo) override
    {
        return new BTAssetInfo(dynamic_cast<BTAssetInfo&>(assetInfo));
    }

};

