#pragma once

#include "Param.h"

class ParamInt : public Param<int>
{

public:

    ParamInt(int def = 0);
    ParamInt(ParamInt& param);

    BaseParam* Copy() override;

    Json toJson() override;
    void fromJson(Json json) override;

protected:

    void UpdateValue(const BaseParam* paramCopy) override;

};

