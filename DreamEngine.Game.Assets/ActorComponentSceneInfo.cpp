#include "ActorComponentSceneInfo.h"
#include "MapUtils.h"
#include "ErrorLogger.h"

ActorComponentSceneInfo::ActorComponentSceneInfo(ACS_Type type)
    : ActorComponentInfo(), type(type)
{
}

ActorComponentSceneInfo::ActorComponentSceneInfo(ActorComponentSceneInfo& componentInfo)
    : ActorComponentInfo(componentInfo)
{
    type = componentInfo.type;
}

ACS_Type ActorComponentSceneInfo::GetType() const
{
    return type;
}

Json ActorComponentSceneInfo::toJson()
{
    Json json = ActorComponentInfo::toJson();

    json["type"] = MapUtils::TryGetByKey<ACS_Type, std::string>(MAP_ACS_TYPE_TO_STRING, type, "UNKNOWN");

    return json;
}

void ActorComponentSceneInfo::fromJson(Json json)
{
    ActorComponentInfo::fromJson(json);

    std::string stringType;
    initVariable(json, "type", &stringType);
    type = MapUtils::TryGetByValue<ACS_Type, std::string>(MAP_ACS_TYPE_TO_STRING, stringType, ACS_Type::UNKNOWN);
    if (type == ACS_Type::UNKNOWN)
        ErrorLogger::Log(Error, "SceneActorInfo has invalid type: " + stringType + "/n" + json.dump());
}


