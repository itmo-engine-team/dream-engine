#include "ParamFloat.h"

ParamFloat::ParamFloat(float def) : Param<float>(ParamType::Float, def)
{

}

ParamFloat::ParamFloat(ParamFloat& param) : Param<float>(param)
{

}

BaseParam* ParamFloat::Copy()
{
    return new ParamFloat(*this);
}

Json ParamFloat::toJson()
{
    Json json = Param::toJson();

    json["value"] = value;

    return json;
}

void ParamFloat::fromJson(Json json)
{
    Param::fromJson(json);

    initVariable(json, "value", &value);
}

void ParamFloat::UpdateValue(const BaseParam* paramCopy)
{
    if (paramCopy->IsDefault())
        SetDef();
    else
        Set(dynamic_cast<const ParamFloat*>(paramCopy)->Get());
}