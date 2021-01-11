#pragma once

#include "Param.h"

class ParamString : public Param<std::string>
{

public:

    ParamString(std::string def = "");
    ParamString(ParamString& param);

    BaseParam* Copy() override;

    Json toJson() override;
    void fromJson(Json json) override;

protected:

    void UpdateValue(const BaseParam* paramCopy) override;

};