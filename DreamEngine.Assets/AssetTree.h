#pragma once

#include "FolderNode.h"

class AssetTree
{

private:

    AssetTree();
    AssetTree(const AssetTree&) = delete;
    void operator=(const AssetTree&) = delete;

public:

    static AssetTree& GetInstance();
    static FolderNode* GetRootNode();

    FolderNode* CreateFolderNode(std::string nodeName, FolderNode* parentNode);
    AssetNode* CreateAssetNode(std::string nodeName, FolderNode* parentNode);

    void AddAssetNode(AssetNode* assetNode, FolderNode* parentNode);
    void AddFolderNode(FolderNode* folderNode, FolderNode* parentNode);

    void RemoveFolderNode(FolderNode* folderNode, bool isRecursive);
    void RemoveAssetNode(AssetNode* assetNode);

    void MoveFolderNode(FolderNode* folderNode, FolderNode* newParentNode);
    void MoveAssetNode(AssetNode* assetNode, FolderNode* newParentNode);

private:

    static AssetTree instance;
    static FolderNode* rootNode;

};