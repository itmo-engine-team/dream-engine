#include "AssetNode.h"

AssetNode::AssetNode(std::string nodeName, FolderNode* parentNode)
{
    NodeName = nodeName;
    ParentNode = parentNode;
}

std::string AssetNode::GetNodeName()
{
    return NodeName;
}

FolderNode* AssetNode::GetParentNode()
{
    return ParentNode;
}

AssetNode::AssetNode()
{
}

void AssetNode::SetNodeName(std::string nodeName)
{
    NodeName = nodeName;
}

void AssetNode::SetParentNode(FolderNode* parentNode)
{
    ParentNode = parentNode;
}
