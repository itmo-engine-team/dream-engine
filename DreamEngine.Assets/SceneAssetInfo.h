#pragma once

#include "AssetInfo.h"
#include "SceneActorInfo.h"

class SceneAssetInfo : public AssetInfo
{

public:

    SceneAssetInfo();
    SceneAssetInfo(SceneAssetInfo& assetInfo);

protected:

    Json toJson() override;
    void fromJson(Json json) override;

private:

    std::vector<SceneActorInfo*> actorInfoList;

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