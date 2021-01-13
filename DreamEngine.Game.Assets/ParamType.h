#pragma once

enum class ParamType
{
    Int,
    Float,
    Asset,
    Transform,
    String,
    Bool,
    Vector3
};

const std::map<ParamType, std::string> MAP_PARAM_TYPE_TO_STRING = {
    { ParamType::Int, "Int" },
    { ParamType::Float, "Float" },
    { ParamType::Asset, "Asset" },
    { ParamType::Transform, "Transform" },
    { ParamType::String, "String" },
    { ParamType::Bool, "Bool" },
    { ParamType::Vector3, "Vector3" }
};
