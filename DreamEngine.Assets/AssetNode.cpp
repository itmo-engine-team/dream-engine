#include "AssetNode.h"

AssetNode::AssetNode(std::string nodeName, FolderNode* parentNode)
{
    nodeStruct.NodeName = nodeName;
    nodeStruct.ParentNode = parentNode;
}

std::string AssetNode::GetNodeName()
{
    return nodeStruct.NodeName;
}

FolderNode* AssetNode::GetParentNode()
{
    return nodeStruct.ParentNode;
}

void AssetNode::SetNodeName(std::string nodeName)
{
    nodeStruct.NodeName = nodeName;
}

void AssetNode::SetParentNode(FolderNode* parentNode)
{
    nodeStruct.ParentNode = parentNode;
}
