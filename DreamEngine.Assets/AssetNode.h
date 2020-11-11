#pragma once

#include <string>
#include "AssetTree.h"
#include "FolderNode.h"

class AssetNode
{

protected:

    struct AssetNodeStruct
    {
        std::string NodeName;
        FolderNode* ParentNode;
    };

public:

    std::string GetNodeName();
    FolderNode* GetParentNode();

protected:

    AssetNode(std::string nodeName, FolderNode* parentNode);
    friend class AssetTree;

    void SetNodeName(std::string nodeName);
    void SetParentNode(FolderNode* parentNode);

private:

    AssetNodeStruct nodeStruct;
};
