#pragma once

#include "AssetInfo.h"

class SceneRoomInfo;

class SceneAssetInfo : public AssetInfo
{

public:

    SceneAssetInfo();
    SceneAssetInfo(SceneAssetInfo& assetInfo);

    const std::vector<SceneRoomInfo*>& GetRoomInfoList() const;

    void AddRoomInfo(SceneRoomInfo* roomInfo);

protected:

    Json toJson() override;
    void fromJson(Json json) override;

private:

    std::vector<SceneRoomInfo*> roomInfoList;

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