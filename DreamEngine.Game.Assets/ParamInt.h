#pragma once

#include "Param.h"

class ParamInt : public Param<int>
{

public:

    ParamInt(int def);
    ParamInt(ParamInt& param);
    ParamInt(Json json);

    BaseParam* Copy() override;

    Json toJson() override;
    void fromJson(Json json) override;

protected:

    void UpdateValue(const BaseParam* paramCopy) override;

};

