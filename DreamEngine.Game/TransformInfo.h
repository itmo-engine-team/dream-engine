#pragma once

#include "SimpleMath.h"
#include "Transform.h"

using namespace DirectX::SimpleMath;

class TransformInfo
{

public:

    TransformInfo();

    Vector3 GetPosition() const;
    void SetPosition(Vector3 pos);

    Transform* CreateTransform() const;

private:

    Vector3 position;

};

