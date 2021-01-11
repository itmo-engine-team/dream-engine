#include "TransformInfo.h"
#include "ErrorLogger.h"

TransformInfo::TransformInfo(Vector3 pos) : position(pos), rotation(Vector3::Zero)
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

Json TransformInfo::toJson()
{
    Json json = Serializable::toJson();

    json["pos"] = JsonUtils::fromVector3(position);
    json["rot"] = JsonUtils::fromVector3(rotation);

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
}
