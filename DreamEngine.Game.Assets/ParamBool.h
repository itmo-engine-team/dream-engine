#pragma once

#include "Param.h"

class ParamBool : public Param<bool>
{

public:

    ParamBool(bool def = false);
    ParamBool(ParamBool& param);

    BaseParam* Copy() override;

    Json toJson() override;
    void fromJson(Json json) override;

protected:

    void UpdateValue(const BaseParam* paramCopy) override;

};

