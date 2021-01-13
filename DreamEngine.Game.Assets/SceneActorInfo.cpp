#include "SceneActorInfo.h"
#include "MapUtils.h"
#include "ErrorLogger.h"
#include "ParamTransform.h"
#include "ParamAsset.h"
#include "AssetType.h"

SceneActorInfo::SceneActorInfo(ActorType type)
{
    paramTransform = new ParamTransform();
    paramAsset = new ParamAsset(AssetType::Actor);
}

Actor* SceneActorInfo::GetActor() const
{
    return actor;
}

void SceneActorInfo::SetActor(Actor* actor)
{
    this->actor = actor;
}

const std::string& SceneActorInfo::GetName() const
{
    return name;
}

void SceneActorInfo::SetName(const std::string& name)
{
    this->name = name;
}

ParamTransform* SceneActorInfo::GetParamTransform() const
{
    return paramTransform;
}

ParamAsset* SceneActorInfo::GetParamAsset() const
{
    return paramAsset;
}

Json SceneActorInfo::toJson()
{
    Json json = Serializable::toJson();

    json["name"] = name;
    json["transform"] = paramTransform->toJson();
    json["asset"] = paramAsset->toJson();

    return json;
}

void SceneActorInfo::fromJson(Json json)
{
    initVariable(json, "name", &name);

    paramTransform->fromJson(json["transform"]);
    paramAsset->fromJson(json["asset"]);
    
}

