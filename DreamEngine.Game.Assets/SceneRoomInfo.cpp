#include "SceneRoomInfo.h"

#include "SceneActorInfo.h"

const std::string& SceneRoomInfo::GetName() const
{
    return name;
}

void SceneRoomInfo::SetName(const std::string& name)
{
    this->name = name;
}

const std::vector<SceneActorInfo*>& SceneRoomInfo::GetActorInfoList() const
{
    return actorInfoList;
}

Json SceneRoomInfo::toJson()
{
    Json json = Serializable::toJson();

    json["name"] = name;

    Json jsonActorArray = Json::array();
    for (auto actorInfo : actorInfoList)
    {
        jsonActorArray.push_back(actorInfo->toJson());
    }
    json["actors"] = jsonActorArray;

    return json;
}

void SceneRoomInfo::fromJson(Json json)
{
    initVariable(json, "name", &name);

    Json jsonActorArray = json["actors"];
    for (auto jsonActorInfo : jsonActorArray)
    {
        auto actorInfo = new SceneActorInfo();
        actorInfo->fromJson(jsonActorInfo);
        actorInfoList.push_back(actorInfo);
    }
}
