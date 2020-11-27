#pragma once

#include "SimpleMath.h"

using namespace DirectX::SimpleMath;

struct alignas(sizeof(Vector4)) CameraBuffer
{
    Vector3 CameraPosition;
};