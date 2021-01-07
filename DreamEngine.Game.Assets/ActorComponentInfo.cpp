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

ActorComponent* ActorComponentInfo::GetComponentRef() const
{
    return componentRef;
}

void ActorComponentInfo::SetComponentRef(ActorComponent* componentRef)
{
    this->componentRef = componentRef;
}

ParamExtender* ActorComponentInfo::GetParamExtender() const
{
    return paramExtender;
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
