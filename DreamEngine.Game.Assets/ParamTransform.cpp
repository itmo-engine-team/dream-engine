#include "ParamTransform.h"

ParamTransform::ParamTransform(TransformInfo def) : Param<TransformInfo>(ParamType::Transform, def)
{
    
}

ParamTransform::ParamTransform(ParamTransform& paramTransform) : Param<TransformInfo>(paramTransform)
{

}

BaseParam* ParamTransform::Copy()
{
    return new ParamTransform(*this);
}

Vector3 ParamTransform::GetPosition() const
{
    return value.GetPosition();
}

void ParamTransform::SetPosition(Vector3 position)
{
    value.SetPosition(position);
    isDefault = false;
}

void ParamTransform::SetDefPosition()
{
    value.SetPosition(def.GetPosition());
    isDefault = true;
}

void ParamTransform::UpdateValue(const BaseParam* paramCopy)
{
    if (paramCopy->IsDefault())
    {
        SetDef();
    }
    else
    {
        value.SetPosition(dynamic_cast<const ParamTransform*>(paramCopy)->GetPosition());
        isDefault = false;
    }
}

Json ParamTransform::toJson()
{
    Json json = Param::toJson();

    json["value"] = value.toJson();

    return json;
}

void ParamTransform::fromJson(Json json)
{
    Param::fromJson(json);

    value = {};
    value.fromJson(json["value"]);
}
