#pragma once

#include <map>
#include <string>

#include "AssetInfo.h"
#include "ActorAssetInfo.h"
#include "TextureAssetInfo.h"
#include "ModelAssetInfo.h"

class AssetInfoFactory
{

public:

    inline static std::map<AssetType, std::string> MAP_ASSET_TYPE_TO_STRING = {
        { AssetType::Actor, "Actor" },
        { AssetType::Scene, "Scene" },
        { AssetType::Model, "Model" },
        { AssetType::Texture, "Texture" },
    };

    static AssetInfo* Create(const AssetType type)
    {
        return creators[type]->Create();
    }
    
    static AssetInfo* Duplicate(AssetInfo& assetInfo)
    {
        return creators[assetInfo.GetAssetType()]->Duplicate(assetInfo);
    }

private:

    inline static std::unordered_map<AssetType, AssetInfoCreator*> creators = {
        { AssetType::Actor, new ActorAssetInfoCreator() }, 
        { AssetType::Model, new ModelAssetInfoCreator() }, 
        { AssetType::Texture, new TextureAssetInfoCreator() }, 
    };

};

