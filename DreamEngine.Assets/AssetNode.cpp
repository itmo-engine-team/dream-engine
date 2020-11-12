#include "AssetNode.h"

AssetNode::AssetNode()
{
}

AssetNode::AssetNode(std::string nodeName, FolderNode* parentNode)
{
    name = nodeName;
    parent = parentNode;
}

std::string AssetNode::GetName()
{
    return name;
}

FolderNode* AssetNode::GetParent()
{
    return parent;
}

void AssetNode::setNodeName(std::string nodeName)
{
    name = nodeName;
}

void AssetNode::setParentNode(FolderNode* parentNode)
{
    parent = parentNode;
}
