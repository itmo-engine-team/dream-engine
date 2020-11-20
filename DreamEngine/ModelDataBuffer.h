#pragma once

#include <SimpleMath.h>

using namespace DirectX::SimpleMath;

struct alignas(sizeof(Vector4)) ModelDataBuffer
{
    float HasTexture; // bool
    float HasLight; // bool
    float HasShadow; // bool
};
