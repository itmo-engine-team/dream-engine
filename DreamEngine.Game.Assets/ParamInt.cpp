#include "ParamInt.h"

ParamInt::ParamInt(int def) : Param<int>(ParamType::Int, def)
{

}

ParamInt::ParamInt(ParamInt& param) : Param<int>(param)
{
    
}

BaseParam* ParamInt::Copy()
{
    return new ParamInt(*this);
}

Json ParamInt::toJson()
{
    Json json = Param::toJson();

    json["value"] = value;

    return json;
}

void ParamInt::fromJson(Json json)
{
    Param::fromJson(json);

    initVariable(json, "value", &value);
}

void ParamInt::UpdateValue(const BaseParam* paramCopy)
{
    if (paramCopy->IsDefault())
        SetDef();
    else
        Set(dynamic_cast<const ParamInt*>(paramCopy)->Get());
}
