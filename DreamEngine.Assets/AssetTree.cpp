#include "AssetTree.h"

FolderNode* AssetTree::rootnode = new FolderNode("Content", nullptr);

AssetTree& AssetTree::GetInstance()
{
    return instance;
}

void AssetTree::AddAssetNode(AssetNode* assetNode, FolderNode* parentNode)
{
    parentNode->SetChildAssetNode(assetNode);
    assetNode->SetParentNode(parentNode);
}

void AssetTree::AddFolderNode(FolderNode* folderNode, FolderNode* parentNode)
{
    parentNode->SetChildFolderNode(folderNode);
    folderNode->SetParentNode(parentNode);
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
           assetNode->SetParentNode(parentNode);
       }
       parentNode->SetChildAssetNode(folderNode->GetChildAssetNode());

       for (auto* fdNode : folderNode->GetChildFolderNode())
       {
           fdNode->SetParentNode(parentNode);
       }
       parentNode->SetChildFolderNode(folderNode->GetChildFolderNode());

       parentNode->RemoveChildFolderNode(folderNode);
    }
}

void AssetTree::RemoveAssetNode(AssetNode* assetNode)
{
    FolderNode* parenrNode = assetNode->GetParentNode();
    parenrNode->RemoveChildAssetNode(assetNode);
}

void AssetTree::MoveFolderNode(FolderNode* folderNode, FolderNode* newParentNode)
{
    newParentNode->SetChildFolderNode(folderNode);
    folderNode->SetParentNode(newParentNode);
}

void AssetTree::MoveAssetNode(AssetNode* assetNode, FolderNode* newParentNode)
{
    newParentNode->SetChildAssetNode(assetNode);
    assetNode->SetParentNode(newParentNode);
}

AssetTree::AssetTree()
{
}

