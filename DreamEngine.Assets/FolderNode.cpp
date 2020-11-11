#include "FolderNode.h"

FolderNode::FolderNode(std::string nodeName, FolderNode* parentNode)
{
    nodeStruct.NodeName = nodeName;
    nodeStruct.ParentNode = parentNode;
}

std::string FolderNode::GetNodeName()
{
    return nodeStruct.NodeName;
}

FolderNode* FolderNode::GetParentNode()
{
    return nodeStruct.ParentNode;
}

std::vector<FolderNode*> FolderNode::GetChildFolderNode()
{
    return  nodeStruct.ChildFolderNode;
}

std::vector<AssetNode*> FolderNode::GetChildAssetNode()
{
    return  nodeStruct.ChildAssetNode;
}

void FolderNode::SetNodeName(std::string nodeName)
{
    nodeStruct.NodeName = nodeName;
}

void FolderNode::SetParentNode(FolderNode* parentNode)
{
    nodeStruct.ParentNode = parentNode;
}

void FolderNode::SetChildFolderNode(FolderNode* childNode)
{
    nodeStruct.ChildFolderNode.push_back(childNode);
}

void FolderNode::SetChildFolderNode(std::vector<FolderNode*> childNodes)
{
    nodeStruct.ChildFolderNode.insert(std::end(nodeStruct.ChildFolderNode), std::begin(childNodes), std::end(childNodes));
}

void FolderNode::SetChildAssetNode(AssetNode* childNode)
{
    nodeStruct.ChildAssetNode.push_back(childNode);
}

void FolderNode::SetChildAssetNode(std::vector<AssetNode*> childNodes)
{
    nodeStruct.ChildAssetNode.insert(std::end(nodeStruct.ChildAssetNode), std::begin(childNodes), std::end(childNodes));
}
