#pragma once

#include <array>

enum class AssetType
{
    Actor,
    Scene,
    Model,
    Texture,
    Shader,
};

const std::array<AssetType, 5> ALL_ASSET_TYPES = {
    AssetType::Actor,
    AssetType::Scene,
    AssetType::Model,
    AssetType::Texture,
    AssetType::Shader,
};