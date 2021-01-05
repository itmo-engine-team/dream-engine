#pragma once

enum class ACS_Type
{
    Collision,
    StaticModel,

    UNKNOWN
};

const std::map<ACS_Type, std::string> MAP_ACS_TYPE_TO_STRING = {
    { ACS_Type::Collision, "Collision" },
    { ACS_Type::StaticModel, "StaticModel" },
};

enum class ACF_Type
{
    AI,

    UNKNOWN
};

const std::map<ACF_Type, std::string> MAP_ACF_TYPE_TO_STRING = {
    { ACF_Type::AI, "AI" },
};