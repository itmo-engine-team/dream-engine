#pragma once

#include "ActorComponentInfo.h"
#include "ActorComponentType.h"
#include "TransformInfo.h"

class ActorComponentSceneInfo : public ActorComponentInfo
{

public:

    ActorComponentSceneInfo(ACS_Type type = ACS_Type::UNKNOWN);
    ActorComponentSceneInfo(ActorComponentSceneInfo& componentInfo);

    ACS_Type GetType() const;

    Json toJson() override;
    void fromJson(Json json) override;

private:

    ACS_Type type;

};

