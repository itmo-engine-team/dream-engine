#pragma once
#include "Param.h"
class ParamVector3 : public Param<Vector3>
{

public:

    ParamVector3(Vector3 def = Vector3::Zero);
    ParamVector3(ParamVector3& param);

    BaseParam* Copy() override;

    Json toJson() override;
    void fromJson(Json json) override;

protected:

    void UpdateValue(const BaseParam* paramCopy) override;

};