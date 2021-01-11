#include "TransformInfo.h"

TransformInfo::TransformInfo(Vector3 pos) : position(pos), rotation(Vector3::Zero), scale(Vector3::One)
{

}

Vector3 TransformInfo::GetPosition() const
{
    return position;
}

void TransformInfo::SetPosition(Vector3 pos)
{
    position = pos;
}

Vector3 TransformInfo::GetRotation() const
{
    return rotation;
}

void TransformInfo::SetRotation(Vector3 rotation)
{
    this->rotation = rotation;
}

Vector3 TransformInfo::GetScale() const
{
    return scale;
}

void TransformInfo::SetScale(Vector3 scale)
{
    this->scale = scale;
}

Json TransformInfo::toJson()
{
    Json json = Serializable::toJson();

    json["pos"] = JsonUtils::fromVector3(position);
    json["rot"] = JsonUtils::fromVector3(rotation);
    json["scale"] = JsonUtils::fromVector3(scale);

    return json;
}

void TransformInfo::fromJson(Json json)
{
    if (json.contains("pos"))
    {
        position = JsonUtils::toVector3(json["pos"]);
    }

    if (json.contains("rot"))
    {
        rotation = JsonUtils::toVector3(json["rot"]);
    }

    if (json.contains("scale"))
    {
        scale = JsonUtils::toVector3(json["scale"]);
    }
}
