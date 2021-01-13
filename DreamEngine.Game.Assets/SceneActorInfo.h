#pragma once

#include "ActorType.h"
#include "TransformInfo.h"
#include "Serializable.h"

class Actor;
class ParamAsset;
class ParamTransform;

class SceneActorInfo : Serializable
{

public:

    SceneActorInfo(ActorType type = ActorType::Actor);

    Actor* GetActor() const;
    void SetActor(Actor* actor);

    const std::string& GetName() const;
    void SetName(const std::string& name);

    ParamTransform* GetParamTransform() const;
    ParamAsset* GetParamAsset() const;

protected:

    friend class SceneAssetInfo;
    friend class SceneRoomInfo;

    Json toJson() override;
    void fromJson(Json json) override;

private:

    Actor* actor;

    std::string name;
    ParamAsset* paramAsset;
    ParamTransform* paramTransform;

};

