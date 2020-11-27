#include "AssetTree.h"
#include "ErrorLogger.h"

AssetTree::AssetTree(std::string rootNodeName) 
{
    rootNode = new FolderNode(rootNodeName, nullptr);
}

FolderNode* AssetTree::GetRootNode()
{
    return rootNode;
}

FolderNode* AssetTree::CreateFolderNode(const std::string& nodeName, FolderNode* parentNode) const
{
   return new FolderNode(nodeName, parentNode);
}

AssetNode* AssetTree::CreateAssetNode(AssetInfo* assetInfo, const std::string& nodeName, FolderNode* parentNode) const
{
    return new AssetNode(assetInfo, nodeName, parentNode);
}

void AssetTree::AddAssetNode(AssetNode* assetNode, FolderNode* parentNode)
{
    parentNode->addChildAssetNode(assetNode);
    assetNode->setParentNode(parentNode);
}

void AssetTree::AddFolderNode(FolderNode* folderNode, FolderNode* parentNode)
{
    parentNode->addChildFolderNode(folderNode);
    folderNode->setParentNode(parentNode);
}

void AssetTree::RemoveFolderNode(FolderNode* folderNode, bool isRecursive)
{
    if(isRecursive)
    {
        if (folderNode->GetParent() != nullptr)
        {
            folderNode->GetParent()->removeChildFolderNode(folderNode);
        }

        for(AssetNode* assetNode : folderNode->GetChildAssetList())
        {
            RemoveAssetNode(assetNode);
        }

        for (FolderNode* childFolderNode : folderNode->GetChildFolderList())
        {
            RemoveFolderNode(childFolderNode, isRecursive);
        }
        
    }
    else
    {
        if (folderNode->GetParent() == nullptr) return;

        FolderNode* parentNode = folderNode->GetParent();

        parentNode->removeChildFolderNode(folderNode);

        for (auto* assetNode : folderNode->GetChildAssetList())
        {
            assetNode->setParentNode(parentNode);
        }
        parentNode->addChildAssetNodes(folderNode->GetChildAssetList());

        for (auto* childFolderNode : folderNode->GetChildFolderList())
        {
            childFolderNode->setParentNode(parentNode);
        }
        parentNode->addChildFolderNodes(folderNode->GetChildFolderList());

    }

    // Deleted if folderNode != RootNode
    if (folderNode->GetParent() != nullptr)
    {
        delete folderNode;
    }
   
}

void AssetTree::RemoveAssetNode(AssetNode* assetNode)
{
    if (assetNode->GetParent() == nullptr)
    {
        ErrorLogger::Log(Warning, "Cannot remove the assetNode without parent");
        return;
    }
    FolderNode* parentNode = assetNode->GetParent();
    parentNode->removeChildAssetNode(assetNode);

    delete assetNode;
}

void AssetTree::MoveFolderNode(FolderNode* folderNode, FolderNode* newParentNode)
{
    if (folderNode->GetParent() == nullptr)
    {
        ErrorLogger::Log(Warning, "Cannot move the Root folder");
        return;
    }

    newParentNode->addChildFolderNode(folderNode);
    folderNode->GetParent()->removeChildFolderNode(folderNode);
    folderNode->setParentNode(newParentNode);
}

void AssetTree::MoveAssetNode(AssetNode* assetNode, FolderNode* newParentNode)
{
    newParentNode->addChildAssetNode(assetNode);

    if(assetNode->GetParent() != nullptr)
        assetNode->GetParent()->removeChildAssetNode(assetNode);

    assetNode->setParentNode(newParentNode);
}

void AssetTree::ClearAssetTree()
{   
   this->RemoveFolderNode(rootNode, true);
}

