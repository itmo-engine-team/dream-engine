#pragma once

enum class ParamType
{
    Int,
    Float,
    Asset,
    Transform,
    String,
    Bool
};

const std::map<ParamType, std::string> MAP_PARAM_TYPE_TO_STRING = {
    { ParamType::Int, "Int" },
    { ParamType::Float, "Float" },
    { ParamType::Asset, "Asset" },
    { ParamType::Transform, "Transform" },
    { ParamType::String, "String" },
    { ParamType::Bool, "Bool" },
};
