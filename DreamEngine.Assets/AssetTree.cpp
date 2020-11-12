#include "AssetTree.h"

FolderNode* AssetTree::rootnode = new FolderNode("Content", nullptr);

AssetTree& AssetTree::GetInstance()
{
    return instance;
}

void AssetTree::AddAssetNode(AssetNode* assetNode, FolderNode* parentNode)
{
    parentNode->setChildAssetNode(assetNode);
    assetNode->setParentNode(parentNode);
}

void AssetTree::AddFolderNode(FolderNode* folderNode, FolderNode* parentNode)
{
    parentNode->setChildFolderNode(folderNode);
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

        for (FolderNode* fdNode : folderNode->GetChildFolderNode())
        {
            RemoveFolderNode(fdNode, isRecursive);
        }
    }
    else
    {
       FolderNode* parentNode = folderNode->GetParentNode();

       for (auto* assetNode : folderNode->GetChildAssetNode())
       {
           assetNode->setParentNode(parentNode);
       }
       parentNode->setChildAssetNode(folderNode->GetChildAssetNode());

       for (auto* fdNode : folderNode->GetChildFolderNode())
       {
           fdNode->setParentNode(parentNode);
       }
       parentNode->setChildFolderNode(folderNode->GetChildFolderNode());

       parentNode->removeChildFolderNode(folderNode);
    }
}

void AssetTree::RemoveAssetNode(AssetNode* assetNode)
{
    FolderNode* parenrNode = assetNode->GetParentNode();
    parenrNode->removeChildAssetNode(assetNode);
}

void AssetTree::MoveFolderNode(FolderNode* folderNode, FolderNode* newParentNode)
{
    newParentNode->setChildFolderNode(folderNode);
    folderNode->setParentNode(newParentNode);
}

void AssetTree::MoveAssetNode(AssetNode* assetNode, FolderNode* newParentNode)
{
    newParentNode->setChildAssetNode(assetNode);
    assetNode->setParentNode(newParentNode);
}

AssetTree::AssetTree()
{
}

