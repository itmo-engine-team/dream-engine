#pragma once

#include "SimpleMath.h"

using namespace DirectX::SimpleMath;

class TransformInfo
{

public:

    TransformInfo();

    Vector3 GetPosition() const;
    void SetPosition(Vector3 pos);

private:

    Vector3 position;

};

