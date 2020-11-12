#include "AssetTree.h"

FolderNode* AssetTree::rootNode = new FolderNode("Content", nullptr);

AssetTree::AssetTree()
{
}

AssetTree& AssetTree::GetInstance()
{
    return instance;
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
        for(AssetNode* assetNode : folderNode->GetChildAssetNode())
        {
            RemoveAssetNode(assetNode);
        }

        for (FolderNode* childFolderNode : folderNode->GetChildFolderNode())
        {
            RemoveFolderNode(childFolderNode, isRecursive);
        }
    }
    else
    {
        FolderNode* parentNode = folderNode->GetParent();


        parentNode->removeChildFolderNode(folderNode);

        for (auto* assetNode : folderNode->GetChildAssetNode())
        {
            assetNode->setParentNode(parentNode);
        }
        parentNode->addChildAssetNodes(folderNode->GetChildAssetNode());

        for (auto* childFolderNode : folderNode->GetChildFolderNode())
        {
            childFolderNode->setParentNode(parentNode);
        }
        parentNode->addChildFolderNodes(folderNode->GetChildFolderNode());
    }
}

void AssetTree::RemoveAssetNode(AssetNode* assetNode)
{
    FolderNode* parentNode = assetNode->GetParent();
    parentNode->removeChildAssetNode(assetNode);
}

void AssetTree::MoveFolderNode(FolderNode* folderNode, FolderNode* newParentNode)
{
    newParentNode->addChildFolderNode(folderNode);
    folderNode->GetParent()->removeChildFolderNode(folderNode);
    folderNode->setParentNode(newParentNode);
}

void AssetTree::MoveAssetNode(AssetNode* assetNode, FolderNode* newParentNode)
{
    newParentNode->addChildAssetNode(assetNode);
    assetNode->GetParent()->removeChildAssetNode(assetNode);
    assetNode->setParentNode(newParentNode);
}

