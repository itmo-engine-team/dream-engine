#pragma once

#include "SimpleMath.h"
#include "Serializable.h"

using namespace DirectX::SimpleMath;

struct TransformInfo : Serializable
{

    TransformInfo(Vector3 pos = Vector3::Zero);

    Vector3 GetPosition() const;
    void SetPosition(Vector3 pos);

    Vector3 GetRotation() const;
    void SetRotation(Vector3 rotation);

    Vector3 GetScale() const;
    void SetScale(Vector3 scale);

    Json toJson() override;
    void fromJson(Json json) override;

private:

    Vector3 position;
    Vector3 rotation;
    Vector3 scale;

};

