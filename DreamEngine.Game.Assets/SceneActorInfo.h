#pragma once

#include "ActorType.h"
#include "TransformInfo.h"
#include "Serializable.h"

class SceneActorInfo : Serializable
{

public:

    SceneActorInfo(ActorType type = ActorType::Actor);

    ActorType GetType() const;
    void SetType(ActorType type);

    const std::string& GetName() const;
    void SetName(const std::string& name);

    TransformInfo* GetTransformInfo() const;

protected:

    friend class SceneAssetInfo;
    friend class SceneRoomInfo;

    Json toJson() override;
    void fromJson(Json json) override;

private:

    ActorType type;
    std::string name;

    TransformInfo* transformInfo;

};

