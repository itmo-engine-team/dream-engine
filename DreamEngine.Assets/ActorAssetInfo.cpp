#include "ActorAssetInfo.h"

ActorAssetInfo::ActorAssetInfo() : AssetInfo(AssetType::Actor)
{

}

ActorAssetInfo::ActorAssetInfo(ActorAssetInfo& assetInfo) : AssetInfo(assetInfo)
{

}

ActorAssetInfo::~ActorAssetInfo()
{
    for (auto component : sceneComponents)
    {
        delete component;
    }

    for (auto component : fixedComponents)
    {
        delete component;
    }
}

ActorType ActorAssetInfo::GetActorType() const
{
    return actorType;
}

void ActorAssetInfo::SetActorType(ActorType type)
{
    actorType = type;
}

ActorComponentSceneInfo* ActorAssetInfo::AddSceneComponent(ACS_Type type, const std::string& name)
{
    auto sceneComponent = new ActorComponentSceneInfo(type);
    sceneComponent->SetName(name);

    sceneComponents.push_back(sceneComponent);
    return sceneComponent;
}

ActorComponentFixedInfo* ActorAssetInfo::AddFixedComponent(ACF_Type type, const std::string& name)
{
    auto fixedComponent = new ActorComponentFixedInfo(type);
    fixedComponent->SetName(name);

    fixedComponents.push_back(fixedComponent);
    return fixedComponent;
}

const std::vector<ActorComponentSceneInfo*>& ActorAssetInfo::GetSceneComponents() const
{
    return sceneComponents;
}

const std::vector<ActorComponentFixedInfo*>& ActorAssetInfo::GetFixedComponents() const
{
    return fixedComponents;
}

Json ActorAssetInfo::toJson()
{
    Json json = AssetInfo::toJson();

    Json sceneComponentsJson = Json::array();
    for (auto component : sceneComponents)
    {
        sceneComponentsJson.push_back(component->toJson());
    }
    json["sceneComponents"] = sceneComponentsJson;

    Json fixedComponentsJson = Json::array();
    for (auto component : fixedComponents)
    {
        fixedComponentsJson.push_back(component->toJson());
    }
    json["fixedComponents"] = fixedComponentsJson;

    return json;
}

void ActorAssetInfo::fromJson(Json json)
{
    AssetInfo::fromJson(json);

    Json sceneComponentsJson = json["sceneComponents"];
    for (auto componentJson : sceneComponentsJson)
    {
        ActorComponentSceneInfo* sceneComponent = new ActorComponentSceneInfo();
        sceneComponent->fromJson(componentJson);
        sceneComponents.push_back(sceneComponent);
    }

    Json fixedComponentsJson = json["fixedComponents"];
    for (auto componentJson : fixedComponentsJson)
    {
        ActorComponentFixedInfo* fixedComponent = new ActorComponentFixedInfo();
        fixedComponent->fromJson(componentJson);
        fixedComponents.push_back(fixedComponent);
    }
}
