#include "ParamString.h"

ParamString::ParamString(std::string def) : Param<std::string>(ParamType::String, def)
{

}

ParamString::ParamString(ParamString& param) : Param<std::string>(param)
{

}

BaseParam* ParamString::Copy()
{
    return new ParamString(*this);
}

Json ParamString::toJson()
{
    Json json = {};

    json["value"] = value;
    json["def"] = def;

    return json;
}

void ParamString::fromJson(Json json)
{
    initVariable(json, "value", &value);
    initVariable(json, "def", &def);
}

void ParamString::UpdateValue(const BaseParam* paramCopy)
{
    this->Set(dynamic_cast<const ParamString*>(paramCopy)->Get());
}