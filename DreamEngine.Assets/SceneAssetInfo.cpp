#include "SceneAssetInfo.h"

#include "SceneRoomInfo.h"

SceneAssetInfo::SceneAssetInfo() : AssetInfo(AssetType::Scene)
{

}

SceneAssetInfo::SceneAssetInfo(SceneAssetInfo& assetInfo) : AssetInfo(assetInfo)
{

}

const std::vector<SceneRoomInfo*>& SceneAssetInfo::GetRoomInfoList() const
{
    return roomInfoList;
}

void SceneAssetInfo::AddRoomInfo(SceneRoomInfo* roomInfo)
{
    roomInfoList.push_back(roomInfo);
}

Json SceneAssetInfo::toJson()
{
    Json json = AssetInfo::toJson();
    Json jsonInfo = {};

    Json jsonRoomArray = Json::array();
    for (auto roomInfo : roomInfoList)
    {
        jsonRoomArray.push_back(roomInfo->toJson());
    }

    jsonInfo["rooms"] = jsonRoomArray;
    json["info"] = jsonInfo;

    return json;
}

void SceneAssetInfo::fromJson(Json json)
{
    AssetInfo::fromJson(json);

    Json jsonInfo = json["info"];
    Json jsonRoomArray = jsonInfo["rooms"];
    for (auto jsonRoomInfo : jsonRoomArray)
    {
        auto roomInfo = new SceneRoomInfo();
        roomInfo->fromJson(jsonRoomInfo);
        roomInfoList.push_back(roomInfo);
    }
}
