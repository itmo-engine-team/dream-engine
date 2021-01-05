#include "ActorComponentFixedInfo.h"
#include "MapUtils.h"
#include "ErrorLogger.h"

ActorComponentFixedInfo::ActorComponentFixedInfo(ACF_Type type)
    : ActorComponentInfo(), type(type)
{

}

ActorComponentFixedInfo::~ActorComponentFixedInfo()
{
    
}

Json ActorComponentFixedInfo::toJson()
{
    Json json = ActorComponentInfo::toJson();

    json["type"] = MapUtils::TryGetByKey<ACF_Type, std::string>(MAP_ACF_TYPE_TO_STRING, type, "UNKNOWN");

    return json;
}

void ActorComponentFixedInfo::fromJson(Json json)
{
    ActorComponentInfo::fromJson(json);

    std::string stringType;
    initVariable(json, "type", &stringType);
    type = MapUtils::TryGetByValue<ACF_Type, std::string>(MAP_ACF_TYPE_TO_STRING, stringType, ACF_Type::UNKNOWN);
    if (type == ACF_Type::UNKNOWN)
        ErrorLogger::Log(Error, "SceneActorInfo has invalid type: " + stringType + "/n" + json.dump());
}
