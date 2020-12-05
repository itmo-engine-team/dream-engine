#pragma once

#include "AssetType.h"

class AssetManager;

class AssetInfo
{

public:

    AssetInfo(AssetType type);
    ~AssetInfo() = default;

    unsigned int GetId() const;

    AssetType GetAssetType() const;

protected:

    unsigned int id;

    AssetType type;

private:

    friend AssetManager;

    void setId(unsigned int id);

};

