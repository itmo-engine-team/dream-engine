#include "pch.h"

#include "AssetServices.h"

TEST(AssetTest, CreateAsset)
{
    AssetTree* assetTree = AssetServices::FindAssetTree("Content");
    AssetNode* assetNode = assetTree->CreateAssetNode(nullptr, "Person", assetTree->GetRootNode());
    AssetServices::CreateAssetFile(assetNode);

}

TEST(AssetTest, RemoveAsset)
{    
    AssetTree* assetTree = AssetServices::FindAssetTree("Content");

    AssetServices::RemoveAssetFile(assetTree->GetRootNode()->GetChildAssetList()[0]);
    assetTree->RemoveAssetNode(assetTree->GetRootNode()->GetChildAssetList()[0]);
}

TEST(AssetTest, CreateFolders)
{
    AssetTree* assetTree = AssetServices::FindAssetTree("Content");

    // First layer
    FolderNode* folderNode = assetTree->CreateFolderNode("Folder1", assetTree->GetRootNode());
    AssetServices::CreateFolder(folderNode);

    AssetNode* assetNode = assetTree->CreateAssetNode(nullptr, "Person1", folderNode);
    AssetServices::CreateAssetFile(assetNode);

    // Second Layer
    folderNode = assetTree->CreateFolderNode("Folder2", assetTree->GetRootNode()->GetChildFolderList()[0]);
    AssetServices::CreateFolder(folderNode);

    assetNode = assetTree->CreateAssetNode(nullptr, "Person2.1", folderNode);
    AssetServices::CreateAssetFile(assetNode);

    assetNode = assetTree->CreateAssetNode(nullptr, "Person2.2", folderNode);
    AssetServices::CreateAssetFile(assetNode);

    // Third Layer

    folderNode = assetTree->CreateFolderNode("Folder3.1", assetTree->GetRootNode()->GetChildFolderList()[0]->GetChildFolderList()[0]);
    AssetServices::CreateFolder(folderNode);

    assetNode = assetTree->CreateAssetNode(nullptr, "Person3.1", folderNode);
    AssetServices::CreateAssetFile(assetNode);

    folderNode = assetTree->CreateFolderNode("Folder3.2", assetTree->GetRootNode()->GetChildFolderList()[0]->GetChildFolderList()[0]);
    AssetServices::CreateFolder(folderNode);

    assetNode = assetTree->CreateAssetNode(nullptr, "Person3.2", folderNode);
    AssetServices::CreateAssetFile(assetNode);
}

TEST(AssetTest, RecursiveRemoveFolder)
{
    AssetTree* assetTree = AssetServices::FindAssetTree("Content");

    FolderNode* folderNode = assetTree->GetRootNode()->GetChildFolderList()[0];

    AssetServices::RemoveFolder(folderNode, true);
    assetTree->RemoveFolderNode(folderNode, true);
}

TEST(AssetTest, NoRecursiveRemoveFolder)
{
    AssetTree* assetTree = AssetServices::FindAssetTree("Content");

    FolderNode* folderNode = assetTree->GetRootNode()->GetChildFolderList()[0];

    AssetServices::RemoveFolder(folderNode, false);
    assetTree->RemoveFolderNode(folderNode, false);
}