#pragma once

#include <map>
#include <set>

#include "AssetInfo.h"
#include "AssetTree.h"

class AssetManager
{

public:

    AssetManager();
    ~AssetManager();

    AssetModificationResult CreateAsset(AssetType assetType, const std::string& assetName, FolderNode* parentFolderNode);
    AssetModificationResult RemoveAsset(AssetNode* assetNode);
    AssetModificationResult RenameAsset(AssetNode* assetNode, const std::string& newName);
    AssetModificationResult DuplicateAsset(AssetNode* assetNode, const std::string& newName);
    AssetModificationResult MoveAsset(AssetNode* assetNode, FolderNode* newParentFolderNode);
    AssetModificationResult SaveAsset(AssetNode* assetNode);

    FolderModificationResult CreateFolder(const std::string& assetName, FolderNode* parentFolderNode);
    FolderModificationResult RemoveFolder(FolderNode* folderNode, bool isRecursive);
    FolderModificationResult RenameFolder(FolderNode* folderNode, const std::string& newName);
    FolderModificationResult MoveFolder(FolderNode* folderNode, FolderNode* newParentFolderNode);

    AssetTree* GetContentAssetTree() const;

    const std::map<unsigned int, AssetInfo*>& GetAssetMapByType(AssetType type) const;
    AssetInfo* GetAssetByType(AssetType type, unsigned int id) const;

private:

    // Debug flag to use debug tree
    bool isDebugTree = false;

    std::map<AssetType, std::map<unsigned int, AssetInfo*>> assetMap;
    std::set<unsigned int> idSet;

    AssetTree* contentAssetTree;

    void initAssetTree(AssetTree* assetTree);

    AssetModificationResult addNewAsset(AssetInfo* assetInfo, FolderNode* parentFolderNode);
    bool addAssetInfoToMap(AssetInfo* assetInfo);

    unsigned int generateNewId() const;

};

