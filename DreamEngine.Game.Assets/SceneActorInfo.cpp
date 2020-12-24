#include "SceneActorInfo.h"
#include "MapUtils.h"

SceneActorInfo::SceneActorInfo(ActorType type)
    : type(type), transformInfo(new TransformInfo())
{
    
}

ActorType SceneActorInfo::GetType() const
{
    return type;
}

void SceneActorInfo::SetType(ActorType type)
{
    this->type = type;
}

const std::string& SceneActorInfo::GetName() const
{
    return name;
}

void SceneActorInfo::SetName(const std::string& name)
{
    this->name = name;
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

    delete transformInfo;
    transformInfo = new TransformInfo();
    transformInfo->fromJson(json["transform"]);
}

