#include "SceneActorInfo.h"
#include "MapUtils.h"

SceneActorInfo::SceneActorInfo(ActorType type) : type(type)
{
    
}

ActorType SceneActorInfo::GetType() const
{
    return type;
}

TransformInfo* SceneActorInfo::GetTransformInfo() const
{
    return transformInfo;
}

Json SceneActorInfo::toJson()
{
    Json json = Serializable::toJson();

    json["type"] = MapUtils::TryGetByKey<ActorType, std::string>(MAP_ACTOR_TYPE_TO_STRING, type, "Unknown");
    json["transform"] = transformInfo->toJson();

    return json;
}

void SceneActorInfo::fromJson(Json json)
{
    std::string stringType;
    initVariable(json, "type", &stringType);
    type = MapUtils::TryGetByValue<ActorType, std::string>(MAP_ACTOR_TYPE_TO_STRING, stringType, ActorType::Unknown);

    transformInfo = new TransformInfo();
    transformInfo->fromJson(json["transform"]);
}

