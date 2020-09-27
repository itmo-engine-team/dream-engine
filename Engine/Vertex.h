#pragma once

#include "SimpleMath.h"

using namespace DirectX::SimpleMath;

class Vertex
{
public:

    Vector3 pos;
    Vector4 color;
    Vector3 normal;
    Vector2 texCord;

    Vertex() = default;
    Vertex(Vector3 p, Vector4 c, Vector3 n) : pos(p), color(c), normal(n) {

    }
    Vertex operator+(Vertex const v) {
        Vertex vNew;
        vNew.pos.x = v.pos.x + pos.x;
        vNew.pos.y = v.pos.y + pos.y;
        vNew.color = color;
        return vNew;
    }

    Vertex operator*(float const v) {
        Vertex vNew;
        vNew.pos.x = pos.x * v;
        vNew.pos.y = pos.y * v;
        vNew.color = color;
        return vNew;
    }
};