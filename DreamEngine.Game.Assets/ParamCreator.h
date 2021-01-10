#pragma once

#include "Param.h"
#include "ParamInt.h"
#include "ParamAsset.h"
#include "ParamTransform.h"

class ParamCreator
{
    static BaseParam* CreateParam(ParamType type)
    {
        switch (type)
        {
            case ParamType::Int:
                return new ParamInt(0);
            case ParamType::Float:
                break;
            case ParamType::Asset:
                return new ParamAsset();
            case ParamType::Transform:
                return new ParamTransform();
            default:
                return nullptr;
        }
    }
};

