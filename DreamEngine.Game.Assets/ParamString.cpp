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
    Json json = Param::toJson();

    json["value"] = value;

    return json;
}

void ParamString::fromJson(Json json)
{
    Param::fromJson(json);

    initVariable(json, "value", &value);
}

void ParamString::UpdateValue(const BaseParam* paramCopy)
{
    if (paramCopy->IsDefault())
        SetDef();
    else
        Set(dynamic_cast<const ParamString*>(paramCopy)->Get());
}