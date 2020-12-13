#pragma once

#include "AssetInfo.h"

class ActorAssetInfo : public AssetInfo
{

public:

    ActorAssetInfo();
    ActorAssetInfo(ActorAssetInfo& assetInfo);

protected:

    Json toJson() override;
    void fromJson(Json json) override;

};

class ActorAssetInfoCreator : public AssetInfoCreator
{

    AssetInfo* Create() override
    {
        return new ActorAssetInfo();
    }

    AssetInfo* Duplicate(AssetInfo& assetInfo) override
    {
        return new ActorAssetInfo(dynamic_cast<ActorAssetInfo&>(assetInfo));
    }

};