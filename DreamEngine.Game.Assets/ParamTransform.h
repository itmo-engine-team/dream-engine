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

    Vector3 GetRotation() const;
    void SetRotation(Vector3 rotation);
    void SetDefRotation();

    Vector3 GetScale() const;
    void SetScale(Vector3 scale);
    void SetDefScale();

protected:

    void UpdateValue(const BaseParam* paramCopy) override;

public:

    Json toJson() override;
    void fromJson(Json json) override;

};

