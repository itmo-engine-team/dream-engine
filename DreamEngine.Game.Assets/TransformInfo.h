#pragma once

#include "SimpleMath.h"
#include "Serializable.h"

using namespace DirectX::SimpleMath;

class TransformInfo : Serializable
{

public:

    TransformInfo();

    Vector3 GetPosition() const;
    void SetPosition(Vector3 pos);

protected:

    Json toJson() override;
    void fromJson(Json json) override;

private:

    Vector3 position;

};

