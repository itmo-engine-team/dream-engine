#include "ParamVector3.h"

ParamVector3::ParamVector3(Vector3 def) : Param<Vector3>(ParamType::Vector3, def)
{

}

ParamVector3::ParamVector3(ParamVector3& param) : Param<Vector3>(param)
{

}

BaseParam* ParamVector3::Copy()
{
    return new ParamVector3(*this);
}

Json ParamVector3::toJson()
{
    Json json = Param::toJson();

    json["value"] = JsonUtils::fromVector3(value);

    return json;
}

void ParamVector3::fromJson(Json json)
{
    Param::fromJson(json);

    value = JsonUtils::toVector3(json["value"]);
}

void ParamVector3::UpdateValue(const BaseParam* paramCopy)
{
    if (paramCopy->IsDefault())
        SetDef();
    else
        Set(dynamic_cast<const ParamVector3*>(paramCopy)->Get());
}

