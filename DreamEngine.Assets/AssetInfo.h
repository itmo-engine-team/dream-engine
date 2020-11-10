#pragma once

#include "AssetType.h"

class AssetInfo
{

public:

    AssetInfo(int id, AssetType type);
    ~AssetInfo() = default;

    int GetId() const;
    AssetType GetAssetType() const;

protected:

    int id;
    AssetType type;

};

