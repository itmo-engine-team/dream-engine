#pragma once

#include <string>
#include <vector>
#include "AssetTree.h"
#include "AssetNode.h"

class FolderNode
{

protected:

    struct FolderNodeStruct
    {
        std::string NodeName;
        FolderNode* ParentNode;
        std::vector<FolderNode*> ChildFolderNode;
        std::vector<AssetNode*> ChildAssetNode;
    };

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

private:

    FolderNodeStruct nodeStruct;
};
