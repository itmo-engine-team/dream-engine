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

void FolderNode::setNodeName(std::string nodeName)
{
    NodeName = nodeName;
}

void FolderNode::setParentNode(FolderNode* parentNode)
{
    ParentNode = parentNode;
}

void FolderNode::setChildFolderNode(FolderNode* childNode)
{
    ChildFolderList.push_back(childNode);
}

void FolderNode::setChildFolderNode(std::vector<FolderNode*> childNodes)
{
    ChildFolderList.insert(std::end(ChildFolderList), std::begin(childNodes), std::end(childNodes));
}

void FolderNode::setChildAssetNode(AssetNode* childNode)
{
    ChildAssetList.push_back(childNode);
}

void FolderNode::setChildAssetNode(std::vector<AssetNode*> childNodes)
{
    ChildAssetList.insert(std::end(ChildAssetList), std::begin(childNodes), std::end(childNodes));
}

void FolderNode::removeChildFolderNode(FolderNode* childNode)
{
  auto iterator =  std::find(ChildFolderList.begin(), ChildFolderList.end(), childNode);
  ChildFolderList.erase(iterator);
}

void FolderNode::removeChildAssetNode(AssetNode* childNode)
{
    auto iterator = std::find(ChildAssetList.begin(), ChildAssetList.end(), childNode);
    ChildAssetList.erase(iterator);
}
