#pragma once

#include <map>

#include "AssetInfo.h"
#include "ActorAssetInfo.h"
#include "TextureAssetInfo.h"
#include "ModelAssetInfo.h"

class AssetInfoFactory
{

public:

    static std::string GetAssetTypeStringName(AssetType assetType)
    {
        return MAP_ASSET_TYPE_TO_STRING.find(assetType)->second;
    }

    static AssetType GetAssetTypeByString(std::string stringType)
    {
        return MAP_STRING_TO_ASSET_TYPE.find(stringType)->second;
    }

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

    inline const static std::map<std::string, AssetType> MAP_STRING_TO_ASSET_TYPE = {
        { "Actor", AssetType::Actor },
        { "Scene", AssetType::Scene },
        { "Model", AssetType::Model },
        { "Texture", AssetType::Texture },
    };

    inline const static std::map<AssetType, std::string> MAP_ASSET_TYPE_TO_STRING = {
        { AssetType::Actor, "Actor" },
        { AssetType::Scene, "Scene" },
        { AssetType::Model, "Model" },
        { AssetType::Texture, "Texture" },
    };

};

