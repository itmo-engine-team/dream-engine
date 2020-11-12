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

    void setNodeName(std::string nodeName);
    void setParentNode(FolderNode* parentNode);
    void setChildFolderNode(FolderNode* childNode);
    void setChildFolderNode(std::vector<FolderNode*> childNodes);
    void setChildAssetNode(AssetNode* childNode);
    void setChildAssetNode(std::vector<AssetNode*> childNodes);

    void removeChildFolderNode(FolderNode* childNode);
    void removeChildAssetNode(AssetNode* childNode);


    std::string NodeName;
    FolderNode* ParentNode;
    std::vector<FolderNode*> ChildFolderList;
    std::vector<AssetNode*> ChildAssetList;
};
