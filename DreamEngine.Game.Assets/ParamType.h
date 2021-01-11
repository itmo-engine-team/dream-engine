#pragma once

enum class ParamType
{
    Int,
    Float,
    Asset,
    Transform,
    String
};

const std::map<ParamType, std::string> MAP_ASSET_TYPE_TO_STRING = {
    { ParamType::Int, "Int" },
    { ParamType::Float, "Float" },
    { ParamType::Asset, "Asset" },
    { ParamType::Transform, "Transform" },
    { ParamType::String, "String" },
};
