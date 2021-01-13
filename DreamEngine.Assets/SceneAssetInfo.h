#pragma once

#include "AssetInfo.h"

class SceneRoomInfo;
class SceneActorInfo;
class ParamTransform;

class SceneAssetInfo : public AssetInfo
{

public:

    SceneAssetInfo();
    SceneAssetInfo(SceneAssetInfo& assetInfo);

   /* const std::vector<SceneRoomInfo*>& GetRoomInfoList() const;

    void AddRoomInfo(SceneRoomInfo* roomInfo);*/

    ParamTransform* GetCameraTransformParam() const;

    const std::vector<SceneActorInfo*>& GetActorInfoList() const;
    void AddActorInfo(SceneActorInfo* actorInfo);

protected:

    Json toJson() override;
    void fromJson(Json json) override;

private:

    ParamTransform* cameraTransformParam;

    //std::vector<SceneRoomInfo*> roomInfoList;
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