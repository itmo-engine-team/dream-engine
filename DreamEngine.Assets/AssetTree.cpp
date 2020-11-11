#include "AssetTree.h"

FolderNode* AssetTree::rootnode = new FolderNode("Content", nullptr);

AssetTree& AssetTree::GetInstance()
{
    static AssetTree  instance;
    return instance;
}

AssetTree::AssetTree()
{
}

