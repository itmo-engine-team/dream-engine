#pragma once

#include "SimpleMath.h"

using namespace DirectX::SimpleMath;

struct LightBuffer
{
    Vector4 AmbientColor;
    Vector4 DiffuseColor;
    Vector3 LightDirection;
    float SpecularPower;
    Vector4 SpecularColor;
};