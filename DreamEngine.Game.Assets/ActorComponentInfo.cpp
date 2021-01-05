#include "ActorComponentInfo.h"

ActorComponentInfo::~ActorComponentInfo()
{

}

const std::string& ActorComponentInfo::GetName() const
{
    return name;
}

void ActorComponentInfo::SetName(const std::string& name)
{
    this->name = name;
}

Json ActorComponentInfo::toJson()
{
    Json json = Serializable::toJson();

    json["name"] = name;

    return json;
}

void ActorComponentInfo::fromJson(Json json)
{
    initVariable(json, "name", &name);
}
