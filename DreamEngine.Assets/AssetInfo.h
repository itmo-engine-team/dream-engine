#pragma once

#include "AssetType.h"
#include "Serializable.h"

class AssetManager;

class AssetInfo : public Serializable
{

public:

    AssetInfo(AssetType type);
    AssetInfo(AssetInfo& assetInfo);

    unsigned int GetId() const;
    AssetType GetAssetType() const;

protected:

    unsigned int id;
    AssetType type;

    Json toJson() override;
    void fromJson(Json json) override;

private:

    friend AssetManager;

    void setId(unsigned int id);

};

class AssetInfoCreator
{

public:

    virtual AssetInfo* Create() = 0;
    virtual AssetInfo* Duplicate(AssetInfo& assetInfo) = 0;

};
