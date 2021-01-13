#include "ActorComponentInfo.h"

ActorComponentInfo::ActorComponentInfo(ActorComponentInfo& componentInfo)
{
    name = componentInfo.name;
    paramExtender->CopyParams(componentInfo.paramExtender->GetParamMap());
}

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
    json["params"] = paramExtender->toJson();

    return json;
}

void ActorComponentInfo::fromJson(Json json)
{
    initVariable(json, "name", &name);

    if (json.contains("params"))
    {
        Json paramsJson = json["params"];
        paramExtender->fromJson(paramsJson);
    }
}
