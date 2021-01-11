#include "ParamBool.h"

ParamBool::ParamBool(bool def) : Param<bool>(ParamType::Bool, def)
{

}

ParamBool::ParamBool(ParamBool& param) : Param<bool>(param)
{

}

BaseParam* ParamBool::Copy()
{
    return new ParamBool(*this);
}

Json ParamBool::toJson()
{
    Json json = {};

    json["value"] = value;
    json["def"] = def;

    return json;
}

void ParamBool::fromJson(Json json)
{
    initVariable(json, "value", &value);
    initVariable(json, "def", &def);
}

void ParamBool::UpdateValue(const BaseParam* paramCopy)
{
    this->Set(dynamic_cast<const ParamBool*>(paramCopy)->Get());
}
