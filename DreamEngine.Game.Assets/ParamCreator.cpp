#include "ParamCreator.h"

#include "ParamInt.h"
#include "ParamAsset.h"
#include "ParamTransform.h"
#include "AssetType.h"
#include "MapUtils.h"
#include "ParamFloat.h"
#include "ParamString.h"
#include "ParamBool.h"
#include "ParamVector3.h"

BaseParam* ParamCreator::CreateFromJson(Json json)
{
    std::string stringType = json["type"];
    ParamType type = MapUtils::TryGetByValue<ParamType, std::string>(MAP_PARAM_TYPE_TO_STRING, stringType, ParamType::Int);

    BaseParam* param = nullptr;
    switch (type)
    {
        case ParamType::Int:
            param = new ParamInt();
            break;
        case ParamType::Float:
            param = new ParamFloat();
            break;
        case ParamType::String:
            param = new ParamString();
            break;
        case ParamType::Asset:
            param = new ParamAsset(AssetType::Unknown);
            break;
        case ParamType::Transform:
            param = new ParamTransform();
            break;
        case ParamType::Bool:
            param = new ParamBool();
            break;
        case ParamType::Vector3:
            param = new ParamVector3();
            break;
    }

    if (param == nullptr)
    {
        return nullptr;
    }

    param->fromJson(json);
    return param;
}
