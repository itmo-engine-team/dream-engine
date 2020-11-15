#pragma once

#include <string>

#include "FolderNode.h"

class FolderNode;

class AssetNode
{

public:

    std::string GetName();
    FolderNode* GetParent();

protected:

    friend class AssetTree;
    friend class FolderNode;

    AssetNode();
    AssetNode(std::string nodeName, FolderNode* parentNode);

    void setNodeName(std::string nodeName);
    void setParentNode(FolderNode* parentNode);

private:

    std::string name;
    FolderNode* parent;

};
