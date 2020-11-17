#pragma once

#include "FolderNode.h"

class AssetTree
{

    AssetTree() = default;

public:

    AssetTree(const AssetTree&) = delete;
    void operator=(const AssetTree&) = delete;

    static AssetTree& GetInstance();
    static FolderNode* GetRootNode();

    FolderNode* CreateFolderNode(std::string nodeName, FolderNode* parentNode) const;
    AssetNode* CreateAssetNode(AssetInfo* assetInfo, std::string nodeName, FolderNode* parentNode) const;

    void AddAssetNode(AssetNode* assetNode, FolderNode* parentNode);
    void AddFolderNode(FolderNode* folderNode, FolderNode* parentNode);

    void RemoveFolderNode(FolderNode* folderNode, bool isRecursive);
    void RemoveAssetNode(AssetNode* assetNode);

    void MoveFolderNode(FolderNode* folderNode, FolderNode* newParentNode);
    void MoveAssetNode(AssetNode* assetNode, FolderNode* newParentNode);

    void ClearAssetTree();

private:

    static AssetTree instance;
    static FolderNode* rootNode;

};