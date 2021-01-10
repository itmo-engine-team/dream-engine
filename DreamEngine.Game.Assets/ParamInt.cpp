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
    Json json = {};

    json["value"] = value;
    json["def"] = def;

    return json;
}

void ParamInt::fromJson(Json json)
{
    initVariable(json, "value", &value);
    initVariable(json, "def", &def);
}

void ParamInt::UpdateValue(const BaseParam* paramCopy)
{
    this->Set(dynamic_cast<const ParamInt*>(paramCopy)->Get());
}
