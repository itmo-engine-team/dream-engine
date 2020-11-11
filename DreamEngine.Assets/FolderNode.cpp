#include "FolderNode.h"

FolderNode::FolderNode(std::string nodeName, FolderNode* parentNode)
{
    NodeName = nodeName;
    ParentNode = parentNode;
}

std::string FolderNode::GetNodeName()
{
    return NodeName;
}

FolderNode* FolderNode::GetParentNode()
{
    return ParentNode;
}

std::vector<FolderNode*> FolderNode::GetChildFolderNode()
{
    return  ChildFolderList;
}

std::vector<AssetNode*> FolderNode::GetChildAssetNode()
{
    return  ChildAssetList;
}

void FolderNode::SetNodeName(std::string nodeName)
{
    NodeName = nodeName;
}

void FolderNode::SetParentNode(FolderNode* parentNode)
{
    ParentNode = parentNode;
}

void FolderNode::SetChildFolderNode(FolderNode* childNode)
{
    ChildFolderList.push_back(childNode);
}

void FolderNode::SetChildFolderNode(std::vector<FolderNode*> childNodes)
{
    ChildFolderList.insert(std::end(ChildFolderList), std::begin(childNodes), std::end(childNodes));
}

void FolderNode::SetChildAssetNode(AssetNode* childNode)
{
    ChildAssetList.push_back(childNode);
}

void FolderNode::SetChildAssetNode(std::vector<AssetNode*> childNodes)
{
    ChildAssetList.insert(std::end(ChildAssetList), std::begin(childNodes), std::end(childNodes));
}

void FolderNode::RemoveChildFolderNode(FolderNode* childNode)
{
  auto iterator =  std::find(ChildFolderList.begin(), ChildFolderList.end(), childNode);
  ChildFolderList.erase(iterator);
}

void FolderNode::RemoveChildAssetNode(AssetNode* childNode)
{
    auto iterator = std::find(ChildAssetList.begin(), ChildAssetList.end(), childNode);
    ChildAssetList.erase(iterator);
}
