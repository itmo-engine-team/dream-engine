#include "ParamTransform.h"

ParamTransform::ParamTransform(TransformInfo def) : Param<TransformInfo>(ParamType::Transform, def)
{
    
}

ParamTransform::ParamTransform(ParamTransform& paramTransform) : Param<TransformInfo>(paramTransform)
{
    
}

BaseParam* ParamTransform::Copy()
{
    return new ParamTransform();
}

Vector3 ParamTransform::GetPosition() const
{
    return value.GetPosition();
}

void ParamTransform::SetPosition(Vector3 position)
{
    value.SetPosition(position);
}

void ParamTransform::SetDefPosition()
{
    value.SetPosition(def.GetPosition());
}

void ParamTransform::UpdateValue(const BaseParam* paramCopy)
{
    value.SetPosition(dynamic_cast<const ParamTransform*>(paramCopy)->GetPosition());
}

Json ParamTransform::toJson()
{
    Json json = {};

    json["value"] = value.toJson();
    json["def"] = def.toJson();

    return json;
}

void ParamTransform::fromJson(Json json)
{
    value = {};
    value.fromJson(json["value"]);

    def = {};
    def.fromJson(json["def"]);
}
