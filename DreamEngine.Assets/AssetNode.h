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

    void SetNodeName(std::string nodeName);
    void SetParentNode(FolderNode* parentNode);

    std::string NodeName;
    FolderNode* ParentNode;
};
