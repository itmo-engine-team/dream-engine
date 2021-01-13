#pragma once

#include "AssetInfo.h"
#include "ActorComponentSceneInfo.h"
#include "ActorComponentFixedInfo.h"
#include "ActorType.h"

class ActorAssetInfo : public AssetInfo
{

public:

    ActorAssetInfo();
    ActorAssetInfo(ActorAssetInfo& assetInfo);
    ~ActorAssetInfo();

    ActorType GetActorType() const;
    void SetActorType(ActorType type);

    void RemoveComponent(ActorComponentSceneInfo* component);
    void RemoveComponent(ActorComponentFixedInfo* component);
    ActorComponentSceneInfo* AddSceneComponent(ACS_Type type, const std::string& name);
    ActorComponentFixedInfo* AddFixedComponent(ACF_Type type, const std::string& name);

    const std::vector<ActorComponentSceneInfo*>& GetSceneComponents() const;
    const std::vector<ActorComponentFixedInfo*>& GetFixedComponents() const;

protected:

    Json toJson() override;
    void fromJson(Json json) override;

private:

    ActorType actorType = ActorType::Actor;

    std::vector<ActorComponentSceneInfo*> sceneComponents;
    std::vector<ActorComponentFixedInfo*> fixedComponents;

};

class ActorAssetInfoCreator : public AssetInfoCreator
{

    AssetInfo* Create() override
    {
        return new ActorAssetInfo();
    }

    AssetInfo* Duplicate(AssetInfo& assetInfo) override
    {
        return new ActorAssetInfo(dynamic_cast<ActorAssetInfo&>(assetInfo));
    }

};