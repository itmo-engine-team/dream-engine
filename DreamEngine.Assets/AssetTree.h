#pragma once

#include "FolderNode.h"

class AssetTree
{

public:

    AssetTree(std::string rootNodeName);

    FolderNode* GetRootNode();

    FolderNode* CreateFolderNode(const std::string& nodeName, FolderNode* parentNode) const;
    AssetNode* CreateAssetNode(AssetInfo* assetInfo, const std::string& nodeName, FolderNode* parentNode) const;

    void AddAssetNode(AssetNode* assetNode, FolderNode* parentNode);
    void AddFolderNode(FolderNode* folderNode, FolderNode* parentNode);

    void RemoveFolderNode(FolderNode* folderNode, bool isRecursive);
    void RemoveAssetNode(AssetNode* assetNode);

    void MoveFolderNode(FolderNode* folderNode, FolderNode* newParentNode);
    void MoveAssetNode(AssetNode* assetNode, FolderNode* newParentNode);

    void ClearAssetTree();

private:

    FolderNode* rootNode;

};