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
    Json json = Param::toJson();

    json["value"] = value;

    return json;
}

void ParamBool::fromJson(Json json)
{
    Param::fromJson(json);

    initVariable(json, "value", &value);
}

void ParamBool::UpdateValue(const BaseParam* paramCopy)
{
    if (paramCopy->IsDefault())
        SetDef();
    else
        Set(dynamic_cast<const ParamBool*>(paramCopy)->Get());
}
