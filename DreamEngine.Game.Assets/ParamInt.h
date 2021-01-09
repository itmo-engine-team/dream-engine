#pragma once

#include "Param.h"

class ParamInt : public Param<int>
{

public:

    ParamInt(int def);
    ParamInt(ParamInt& param);

    BaseParam* Copy() override;

protected:

    void UpdateValue(const BaseParam* paramCopy) override;

};

