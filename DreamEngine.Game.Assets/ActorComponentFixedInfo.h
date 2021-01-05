#pragma once

#include "ActorComponentInfo.h"
#include "ActorComponentType.h"
#include "TransformInfo.h"

class ActorComponentFixedInfo : public ActorComponentInfo
{

public:

    ActorComponentFixedInfo(ACF_Type type = ACF_Type::UNKNOWN);
    ~ActorComponentFixedInfo() override;

    Json toJson() override;
    void fromJson(Json json) override;

private:

    ACF_Type type;

};

