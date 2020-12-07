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

    AssetModificationResult AddNewAsset(AssetInfo* assetInfo, const std::string& assetName, FolderNode* parentFolderNode);
    AssetModificationResult RemoveAsset(AssetNode* assetNode);
    AssetModificationResult RenameAsset(AssetNode* assetNode, const std::string& newName);
    AssetModificationResult DuplicateAsset(AssetNode* assetNode);
    AssetModificationResult MoveAsset(AssetNode* assetNode, FolderNode* newParentFolderNode);
    AssetModificationResult SaveAsset(AssetNode* assetNode);

    FolderModificationResult CreateFolder(const std::string& assetName, FolderNode* parentFolderNode);
    FolderModificationResult RemoveFolder(FolderNode* folderNode, bool isRecursive);
    FolderModificationResult RenameFolder(FolderNode* folderNode, const std::string& newName);
    FolderModificationResult MoveFolder(FolderNode* folderNode, FolderNode* newParentFolderNode);

    AssetTree* GetContentAssetTree() const; 

private:

    // Debug flag to use debug tree
    bool isDebugTree = true;

    std::map<unsigned int, AssetInfo*> assetMap;
    std::set<unsigned int> idSet;

    AssetTree* contentAssetTree;

    void initAssetTree(AssetTree* assetTree);
    bool addAssetInfoToMap(AssetInfo* assetInfo);

    unsigned int generateNewId() const;

};

