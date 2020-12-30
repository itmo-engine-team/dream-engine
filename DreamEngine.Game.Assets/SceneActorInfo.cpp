#include "SceneActorInfo.h"
#include "MapUtils.h"

SceneActorInfo::SceneActorInfo(ActorType type)
    : type(type), transformInfo(new TransformInfo())
{
    
}

void SceneActorInfo::SetActor(Actor* actor)
{
    this->actor = actor;
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
    json["name"] = name;
    json["transform"] = transformInfo->toJson();

    return json;
}

void SceneActorInfo::fromJson(Json json)
{
    std::string stringType;
    initVariable(json, "type", &stringType);
    type = MapUtils::TryGetByValue<ActorType, std::string>(MAP_ACTOR_TYPE_TO_STRING, stringType, ActorType::Unknown);

    initVariable(json, "name", &name);

    transformInfo->fromJson(json["transform"]);
}

