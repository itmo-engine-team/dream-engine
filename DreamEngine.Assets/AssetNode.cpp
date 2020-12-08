#include "AssetNode.h"

AssetNode::AssetNode(AssetInfo* assetInfo, std::string nodeName, FolderNode* parentNode)
    : assetInfo(assetInfo), name(std::move(nodeName)), parent(parentNode)
{
    parentNode->addChildAssetNode(this);
}

std::string AssetNode::GetName() const
{
    return name;
}

FolderNode* AssetNode::GetParent() const
{
    return parent;
}

AssetInfo* AssetNode::GetAssetInfo() const
{
    return assetInfo;
}

void AssetNode::setNodeName(std::string nodeName)
{
    name = std::move(nodeName);
}

void AssetNode::setParentNode(FolderNode* parentNode)
{
    parent = parentNode;
}