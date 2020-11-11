#pragma once

#include "AssetNode.h"
#include "FolderNode.h"

class AssetTree
{
public:

    static AssetTree& GetInstance();
    void CreateNode(std::string nodeName);

private:

    AssetTree();
    AssetTree(const AssetTree&) = delete;
    void operator=(const AssetTree&) = delete;

    static FolderNode* rootnode;

};