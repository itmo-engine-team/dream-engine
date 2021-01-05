#include "FolderNode.h"

FolderNode::FolderNode(std::string nodeName, FolderNode* parentNode)
{
    name = nodeName;
    parent = parentNode;
    if (parentNode != nullptr)
        parentNode->addChildFolderNode(this);
}

std::string FolderNode::GetName()
{
    return name;
}

FolderNode* FolderNode::GetParent()
{
    return parent;
}

std::vector<FolderNode*> FolderNode::GetChildFolderList()
{
    return childFolderList;
}

std::vector<AssetNode*> FolderNode::GetChildAssetList()
{
    return childAssetList;
}

void FolderNode::setNodeName(std::string nodeName)
{
    name = nodeName;
}

void FolderNode::setParentNode(FolderNode* parentNode)
{
    parent = parentNode;
}

void FolderNode::addChildFolderNode(FolderNode* childNode)
{
    childFolderList.push_back(childNode);
}

void FolderNode::addChildFolderNodes(std::vector<FolderNode*> childNodes)
{
    childFolderList.insert(std::end(childFolderList), std::begin(childNodes), std::end(childNodes));
}

void FolderNode::addChildAssetNode(AssetNode* childNode)
{
    childAssetList.push_back(childNode);
}

void FolderNode::addChildAssetNodes(std::vector<AssetNode*> childNodes)
{
    childAssetList.insert(std::end(childAssetList), std::begin(childNodes), std::end(childNodes));
}

void FolderNode::removeChildFolderNode(FolderNode* childNode)
{
    auto iterator = std::find(childFolderList.begin(), childFolderList.end(), childNode);
    childFolderList.erase(iterator);
}

void FolderNode::removeChildAssetNode(AssetNode* childNode)
{
    auto iterator = std::find(childAssetList.begin(), childAssetList.end(), childNode);
    childAssetList.erase(iterator);
}
