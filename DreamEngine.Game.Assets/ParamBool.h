#pragma once

#include "Param.h"

class ParamBool : public Param<bool>
{

public:

    ParamBool(bool def);
    ParamBool(ParamBool& param);
    ParamBool(Json json);

    BaseParam* Copy() override;

    Json toJson() override;
    void fromJson(Json json) override;

protected:

    void UpdateValue(const BaseParam* paramCopy) override;

};

