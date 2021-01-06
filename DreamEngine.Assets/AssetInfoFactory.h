#pragma once

#include <map>

#include "AssetInfo.h"
#include "ActorAssetInfo.h"
#include "TextureAssetInfo.h"
#include "ModelAssetInfo.h"
#include "SceneAssetInfo.h"
#include "BTAssetInfo.h"

class AssetInfoFactory
{

public:

    inline const static std::map<std::string, AssetType> MAP_STRING_TO_ASSET_TYPE = {
        { "Actor", AssetType::Actor },
        { "Scene", AssetType::Scene },
        { "Model", AssetType::Model },
        { "Texture", AssetType::Texture },
        { "Behavior Tree", AssetType::BT },
    };

    inline const static std::map<AssetType, std::string> MAP_ASSET_TYPE_TO_STRING = {
        { AssetType::Actor, "Actor" },
        { AssetType::Scene, "Scene" },
        { AssetType::Model, "Model" },
        { AssetType::Texture, "Texture" },
        { AssetType::BT, "Behavior Tree" },
    };

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
        { AssetType::Scene, new SceneAssetInfoCreator() }, 
        { AssetType::Model, new ModelAssetInfoCreator() }, 
        { AssetType::Texture, new TextureAssetInfoCreator() }, 
        { AssetType::BT, new BTAssetInfoCreator() }, 
    };

};

