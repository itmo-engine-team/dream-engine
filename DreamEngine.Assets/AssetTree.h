#pragma once

#include "AssetNode.h"
#include "FolderNode.h"

class AssetTree
{
public:

    static AssetTree& GetInstance();

    void AddAssetNode(AssetNode* assetNode, FolderNode* parentNode);
    void AddFolderNode(FolderNode* folderNode, FolderNode* parentNode);

    void RemoveFolderNode(FolderNode* folderNode, bool isRecursive);
    void RemoveAssetNode(AssetNode* assetNode);

    void MoveFolderNode(FolderNode* folderNode, FolderNode* newParentNode);
    void MoveAssetNode(AssetNode* assetNode, FolderNode* newParentNode);

private:

    AssetTree();
    AssetTree(const AssetTree&) = delete;
    void operator=(const AssetTree&) = delete;

    static AssetTree  instance;
    static FolderNode* rootnode;

};