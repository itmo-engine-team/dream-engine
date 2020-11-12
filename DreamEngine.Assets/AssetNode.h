#pragma once

#include "FolderNode.h"
#include <string>

class FolderNode;

class AssetNode
{

public:

    std::string GetNodeName();
    FolderNode* GetParentNode();

protected:

    AssetNode();
    AssetNode(std::string nodeName, FolderNode* parentNode);
    friend class AssetTree;

    void setNodeName(std::string nodeName);
    void setParentNode(FolderNode* parentNode);

    std::string NodeName;
    FolderNode* ParentNode;
};
