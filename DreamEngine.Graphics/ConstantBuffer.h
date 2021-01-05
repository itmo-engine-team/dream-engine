#pragma once

#include "SimpleMath.h"

using namespace DirectX::SimpleMath;

struct ConstantBuffer
{
    Matrix WorldMatrix;
    Matrix ViewMatrix;
    Matrix ProjectionMatrix;
    Matrix lightView;
    Matrix lightProjection;
};