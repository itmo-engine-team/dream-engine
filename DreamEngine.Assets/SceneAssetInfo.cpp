#include "SceneAssetInfo.h"

#include "SceneActorInfo.h"

SceneAssetInfo::SceneAssetInfo() : AssetInfo(AssetType::Scene)
{

}

SceneAssetInfo::SceneAssetInfo(SceneAssetInfo& assetInfo) : AssetInfo(assetInfo)
{
    actorInfoList = assetInfo.actorInfoList;
}

//const std::vector<SceneRoomInfo*>& SceneAssetInfo::GetRoomInfoList() const
//{
//    return roomInfoList;
//}
//
//void SceneAssetInfo::AddRoomInfo(SceneRoomInfo* roomInfo)
//{
//    roomInfoList.push_back(roomInfo);
//}

const std::vector<SceneActorInfo*>& SceneAssetInfo::GetActorInfoList() const
{
    return actorInfoList;
}

void SceneAssetInfo::AddActorInfo(SceneActorInfo* actorInfo)
{
    actorInfoList.push_back(actorInfo);
}

Json SceneAssetInfo::toJson()
{
    Json json = AssetInfo::toJson();

    Json jsonActorArray = Json::array();
    for (auto actorInfo : actorInfoList)
    {
        jsonActorArray.push_back(actorInfo->toJson());
    }
    json["actors"] = jsonActorArray;

    return json;
}

void SceneAssetInfo::fromJson(Json json)
{
    AssetInfo::fromJson(json);

    Json jsonActorArray = json["actors"];
    for (auto jsonActorInfo : jsonActorArray)
    {
        auto actorInfo = new SceneActorInfo();
        actorInfo->fromJson(jsonActorInfo);
        actorInfoList.push_back(actorInfo);
    }
}

//Json SceneAssetInfo::toJson()
//{
//    Json json = AssetInfo::toJson();
//    Json jsonInfo = {};
//
//    Json jsonRoomArray = Json::array();
//    for (auto roomInfo : roomInfoList)
//    {
//        jsonRoomArray.push_back(roomInfo->toJson());
//    }
//
//    jsonInfo["rooms"] = jsonRoomArray;
//    json["info"] = jsonInfo;
//
//    return json;
//}
//
//void SceneAssetInfo::fromJson(Json json)
//{
//    AssetInfo::fromJson(json);
//
//    Json jsonInfo = json["info"];
//    Json jsonRoomArray = jsonInfo["rooms"];
//    for (auto jsonRoomInfo : jsonRoomArray)
//    {
//        auto roomInfo = new SceneRoomInfo();
//        roomInfo->fromJson(jsonRoomInfo);
//        roomInfoList.push_back(roomInfo);
//    }
//}
