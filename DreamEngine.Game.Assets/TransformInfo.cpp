#include "TransformInfo.h"
#include "ErrorLogger.h"

TransformInfo::TransformInfo() : position(Vector3::Zero)
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

Json TransformInfo::toJson()
{
    Json json = Serializable::toJson();

    json["pos"] = JsonUtils::fromVector3(position);

    return json;
}

void TransformInfo::fromJson(Json json)
{
    if (json.contains("pos"))
    {
        position = JsonUtils::toVector3(json["pos"]);
    }
    else
    {
        ErrorLogger::Log(Error, "TransformInfo json doesn't have pos: \n" + json.dump());
    }
}
