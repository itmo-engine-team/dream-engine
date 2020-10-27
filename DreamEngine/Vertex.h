#pragma once

#include "SimpleMath.h"

using namespace DirectX::SimpleMath;

class Vertex
{
public:

    Vector3 Pos;
    Vector4 Color;
    Vector3 Normal;
    Vector2 TexCord;

    Vertex() = default;
    Vertex(Vector3 p, Vector4 c, Vector3 n) : Pos(p), Color(c), Normal(n) {

    }

    Vertex(Vector3 p, Vector2 t, Vector3 n) : Pos(p), TexCord(t), Normal(n) {

    }

    Vertex operator+(Vertex const v)
	{
        Vertex vNew;
        vNew.Pos.x = v.Pos.x + Pos.x;
        vNew.Pos.y = v.Pos.y + Pos.y;
        vNew.Color = Color;
        return vNew;
    }

    Vertex operator*(float const v)
	{
        Vertex vNew;
        vNew.Pos.x = Pos.x * v;
        vNew.Pos.y = Pos.y * v;
        vNew.Color = Color;
        return vNew;
    }
};