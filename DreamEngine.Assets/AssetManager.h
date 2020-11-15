#pragma once

#include <map>

#include "AssetType.h"
#include "AssetInfo.h"

class AssetManager
{

public:

    AssetManager();
    ~AssetManager();

    template<class AssetInfoClass = AssetInfo>
    AssetInfoClass BuildNewAsset(AssetType type)
    {
        const auto newId = assetLastIdMap[type] + 1;
        assetLastIdMap[type] = newId;

        auto assetInfo = AssetInfoClass(newId);

        return assetInfo;
    }

private:

    std::map<AssetType, std::map<int, AssetInfo*>> assetMap;
    std::map<AssetType, int> assetLastIdMap;

    void addAssetInfoToMap(AssetInfo* assetInfo)
    {
        assetMap[assetInfo->GetAssetType()][assetInfo->GetId()] = assetInfo;
    }

};

