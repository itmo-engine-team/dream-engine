#include "Param.h"

#include "MapUtils.h"

BaseParam::BaseParam(BaseParam& param)
{
    this->type = param.type;
    this->isDefault = param.isDefault;
}

Json BaseParam::toJson()
{
    Json json = Serializable::toJson();
    json["type"] = MapUtils::TryGetByKey<ParamType, std::string>(MAP_PARAM_TYPE_TO_STRING, type, "UNKNOWN");

    return json;
}

void BaseParam::fromJson(Json json)
{
    std::string stringType;
    initVariable(json, "type", &stringType);
    type = MapUtils::TryGetByValue<ParamType, std::string>(MAP_PARAM_TYPE_TO_STRING, stringType, ParamType::Int);
    isDefault = false;
}
