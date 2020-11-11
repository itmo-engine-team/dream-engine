#pragma once

#include "AssetNode.h"
#include <string>
#include <vector>

class AssetNode;

class FolderNode
{

public:

    std::string GetNodeName();
    FolderNode* GetParentNode();
    std::vector<FolderNode*> GetChildFolderNode();
    std::vector<AssetNode*> GetChildAssetNode();

protected:

    FolderNode(std::string nodeName, FolderNode* parentNode);
    friend class AssetTree;

    void SetNodeName(std::string nodeName);
    void SetParentNode(FolderNode* parentNode);
    void SetChildFolderNode(FolderNode* childNode);
    void SetChildFolderNode(std::vector<FolderNode*> childNodes);
    void SetChildAssetNode(AssetNode* childNode);
    void SetChildAssetNode(std::vector<AssetNode*> childNodes);

    void RemoveChildFolderNode(FolderNode* childNode);
    void RemoveChildAssetNode(AssetNode* childNode);


    std::string NodeName;
    FolderNode* ParentNode;
    std::vector<FolderNode*> ChildFolderList;
    std::vector<AssetNode*> ChildAssetList;
};
