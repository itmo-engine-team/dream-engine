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
    Json json = {};

    json["value"] = value;
    json["def"] = def;

    return json;
}

void ParamFloat::fromJson(Json json)
{
    initVariable(json, "value", &value);
    initVariable(json, "def", &def);
}

void ParamFloat::UpdateValue(const BaseParam* paramCopy)
{
    this->Set(dynamic_cast<const ParamFloat*>(paramCopy)->Get());
}