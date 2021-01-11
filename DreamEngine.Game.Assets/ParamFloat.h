#pragma once
#include "Param.h"
class ParamFloat : public Param<float>
{

public:

    ParamFloat(float def);
    ParamFloat(ParamFloat& param);
    ParamFloat(Json json);

    BaseParam* Copy() override;

    Json toJson() override;
    void fromJson(Json json) override;

protected:

    void UpdateValue(const BaseParam* paramCopy) override;

};

