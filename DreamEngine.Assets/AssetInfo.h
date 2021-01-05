#pragma once

#include "AssetType.h"
#include "Serializable.h"

class AssetManager;
class AssetNode;

class AssetInfo : public Serializable
{

public:

    AssetInfo(AssetType type);
    AssetInfo(AssetInfo& assetInfo);
    virtual ~AssetInfo() = default;

    AssetNode* GetAssetNode() const;
    void SetAssetNode(AssetNode* node);

    unsigned int GetId() const;
    AssetType GetAssetType() const;

    const std::string& GetName() const;
    void SetName(const std::string& name);

protected:

    friend AssetService;

    AssetNode* node;

    unsigned int id;
    AssetType type;
    std::string name;

    Json toJson() override;
    void fromJson(Json json) override;

private:

    friend AssetManager;

    void setId(unsigned int id);

};

class AssetInfoCreator
{

public:

    virtual ~AssetInfoCreator() = default;

    virtual AssetInfo* Create() = 0;
    virtual AssetInfo* Duplicate(AssetInfo& assetInfo) = 0;

};
