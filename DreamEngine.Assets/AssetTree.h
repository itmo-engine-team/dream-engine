#pragma once

#include "TreeModificationResult.h"
#include "FolderNode.h"

class AssetTree
{

public:

    AssetTree(std::string rootNodeName);

    FolderNode* GetRootNode();

    FolderModificationResult CreateFolderNode(const std::string& nodeName, FolderNode* parentNode) const;
    AssetModificationResult CreateAssetNode(AssetInfo* assetInfo, const std::string& nodeName, FolderNode* parentNode) const;

    void AddAssetNode(AssetNode* assetNode, FolderNode* parentNode);
    void AddFolderNode(FolderNode* folderNode, FolderNode* parentNode);

    void RemoveFolderNode(FolderNode* folderNode, bool isRecursive);
    void RemoveAssetNode(AssetNode* assetNode);

    void MoveFolderNode(FolderNode* folderNode, FolderNode* newParentNode);
    void MoveAssetNode(AssetNode* assetNode, FolderNode* newParentNode);

    void RenameFolderNode(FolderNode* folderNode, std::string newName);
    void RenameAssetNode(AssetNode* assetNode, std::string newName);

    void ClearAssetTree();

private:

    FolderNode* rootNode;

};