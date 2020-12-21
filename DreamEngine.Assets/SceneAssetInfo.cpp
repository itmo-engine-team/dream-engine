#include "SceneAssetInfo.h"

SceneAssetInfo::SceneAssetInfo() : AssetInfo(AssetType::Scene)
{

}

SceneAssetInfo::SceneAssetInfo(SceneAssetInfo& assetInfo) : AssetInfo(assetInfo)
{

}

Json SceneAssetInfo::toJson()
{
    Json json = AssetInfo::toJson();
    Json jsonInfo = {};

    Json jsonActorArray = Json::array();
    for (auto actorInfo : actorInfoList)
    {
        jsonActorArray.push_back(actorInfo->toJson());
    }

    jsonInfo["actors"] = jsonActorArray;
    json["info"] = jsonInfo;

    return json;
}

void SceneAssetInfo::fromJson(Json json)
{
    AssetInfo::fromJson(json);

    Json jsonInfo = json["info"];
    for (auto jsonActorInfo : json["actors"])
    {
        auto actorInfo = new SceneActorInfo();
        actorInfo->fromJson(jsonActorInfo);
        actorInfoList.push_back(actorInfo);
    }
}
