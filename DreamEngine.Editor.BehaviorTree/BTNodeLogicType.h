#pragma once

#include <map>
#include <string>

enum class BTNodeLogicType
{
    MoveTo,
    TargetNear,
    ReturnFalse,
    ReturnTrue,

    UNKNOWN
};

const std::map<BTNodeLogicType, std::string> MAP_NODE_LOGIC_TYPE_TO_STRING = {
    { BTNodeLogicType::MoveTo, "MoveTo" },
    { BTNodeLogicType::TargetNear, "TargetNear" },
    { BTNodeLogicType::ReturnFalse, "ReturnFalse" },
    { BTNodeLogicType::ReturnTrue, "ReturnTrue" }
};

