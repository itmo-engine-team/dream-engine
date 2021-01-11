#pragma once

#include <vector>
#include <map>
#include <string>

enum class AssetType
{
    Actor,
    Scene,
    Model,
    Texture,
    BT,
    BP,

    Unknown
};

const std::vector<AssetType> ALL_ASSET_TYPES = {
    AssetType::Actor,
    AssetType::Scene,
    AssetType::Model,
    AssetType::Texture,
    AssetType::BT,
};

const std::map<AssetType, std::string> MAP_ASSET_TYPE_TO_STRING = {
    { AssetType::Actor, "Actor" },
    { AssetType::Scene, "Scene" },
    { AssetType::Model, "Model" },
    { AssetType::Texture, "Texture" },
    { AssetType::BT, "Behavior Tree" },
};
