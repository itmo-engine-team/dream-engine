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
}

Vector3 ParamTransform::GetRotation() const
{
    return value.GetRotation();
}

void ParamTransform::SetRotation(Vector3 rotation)
{
    value.SetRotation(rotation);
    isDefault = false;
}

void ParamTransform::SetDefRotation()
{
    value.SetRotation(def.GetRotation());
}

Vector3 ParamTransform::GetScale() const
{
    return value.GetScale();
}

void ParamTransform::SetScale(Vector3 scale)
{
    value.SetScale(scale);
    isDefault = false;
}

void ParamTransform::SetDefScale()
{
    value.SetScale(def.GetScale());
}

void ParamTransform::UpdateValue(const BaseParam* paramCopy)
{
    if (paramCopy->IsDefault())
    {
        SetDef();
    }
    else
    {
        auto castedParamCopy = dynamic_cast<const ParamTransform*>(paramCopy);
        value.SetPosition(castedParamCopy->GetPosition());
        value.SetRotation(castedParamCopy->GetRotation());
        value.SetScale(castedParamCopy->GetScale());
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
