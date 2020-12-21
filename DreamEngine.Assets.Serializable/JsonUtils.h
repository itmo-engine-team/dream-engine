#pragma once

#include "SimpleMath.h"
#include "nlohmann/json.hpp"

using namespace DirectX::SimpleMath;
using Json = nlohmann::json;

class JsonUtils
{

public:

    static Json fromVector3(Vector3 vector3)
    {
        Json json = { vector3.x, vector3.y, vector3.z };
        return json;
    }

    static Vector3 toVector3(Json json)
    {
        return { json[0].get<float>(), json[1].get<float>(), json[2].get<float>() };
    }

};