#pragma once

#include "Param.h"
#include "TransformInfo.h"

class ParamTransform : public Param<TransformInfo>
{

public:

    ParamTransform(TransformInfo def = {});
    ParamTransform(ParamTransform& paramTransform);

    BaseParam* Copy() override;

    Vector3 GetPosition() const;
    void SetPosition(Vector3 position);
    void SetDefPosition();

protected:

    void UpdateValue(const BaseParam* paramCopy) override;

public:

    Json toJson() override;
    void fromJson(Json json) override;

};

