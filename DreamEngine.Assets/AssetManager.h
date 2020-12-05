#pragma once

#include <map>
#include <set>

#include "AssetInfo.h"
#include "AssetType.h"
#include "AssetTree.h"

class AssetManager
{

public:

    AssetManager();
    ~AssetManager();

    void AddNewAsset(AssetInfo* assetInfo, const std::string& assetName, FolderNode* parentFolderNode);

    AssetTree* GetContentAssetTree() const; 

private:

    std::map<AssetType, std::map<unsigned int, AssetInfo*>> assetMap;
    std::set<unsigned int> idSet;

    AssetTree* contentAssetTree;

    void initAssetTree(AssetTree* assetTree);
    void addAssetInfoToMap(AssetInfo* assetInfo);

    unsigned int generateNewId() const;

};

