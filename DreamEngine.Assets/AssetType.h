#pragma once

#include <vector>

enum class AssetType
{
    Actor,
    Scene,
    Model,
    Texture,

    Unknown
};

const std::vector<AssetType> ALL_ASSET_TYPES = {
    AssetType::Actor,
    AssetType::Scene,
    AssetType::Model,
    AssetType::Texture,
};
