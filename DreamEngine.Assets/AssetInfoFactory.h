#pragma once

#include <map>

#include "AssetInfo.h"
#include "ActorAssetInfo.h"
#include "TextureAssetInfo.h"
#include "ModelAssetInfo.h"
#include "SceneAssetInfo.h"
#include "BTAssetInfo.h"
#include "MapUtils.h"

class AssetInfoFactory
{

public:

    static std::string GetAssetTypeStringName(AssetType assetType)
    {
        return MAP_ASSET_TYPE_TO_STRING.find(assetType)->second;
    }

    static AssetType GetAssetTypeByString(std::string stringType)
    {
        return MapUtils::TryGetByValue<AssetType, std::string>(
            MAP_ASSET_TYPE_TO_STRING, stringType, AssetType::Unknown);
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

