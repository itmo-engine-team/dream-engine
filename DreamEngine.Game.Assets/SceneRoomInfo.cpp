#include "SceneRoomInfo.h"

#include "SceneActorInfo.h"

SceneRoomInfo::SceneRoomInfo()
{

}

const std::vector<SceneActorInfo*>& SceneRoomInfo::GetActorInfoList() const
{
    return actorInfoList;
}

Json SceneRoomInfo::toJson()
{
    Json json = Serializable::toJson();
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

void SceneRoomInfo::fromJson(Json json)
{
    Json jsonInfo = json["info"];
    Json jsonActorArray = jsonInfo["actors"];
    for (auto jsonActorInfo : jsonActorArray)
    {
        auto actorInfo = new SceneActorInfo();
        actorInfo->fromJson(jsonActorInfo);
        actorInfoList.push_back(actorInfo);
    }
}
