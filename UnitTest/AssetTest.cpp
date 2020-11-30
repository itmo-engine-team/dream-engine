#include "pch.h"

#include "AssetServices.h"

TEST(AssetTest, CreateAsset)
{
    AssetTree* assetTree = AssetServices::FindAssetTree("Content");
    AssetModificationResult assetResult = assetTree->CreateAssetNode(nullptr, "Person", assetTree->GetRootNode());

    if (assetResult.isSuccess)
        AssetServices::CreateAssetFile(assetResult.assetNode);
    else
        printf(assetResult.error.c_str());   
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
    FolderModificationResult folderResult = assetTree->CreateFolderNode("Folder1", assetTree->GetRootNode());
    if (folderResult.isSuccess)
    {
        AssetServices::CreateFolder(folderResult.folderNode);
    }
    else
    {
        printf(folderResult.error.c_str());
        return;
    }

    AssetModificationResult assetResult = assetTree->CreateAssetNode(nullptr, "Person1", folderResult.folderNode);
    if (assetResult.isSuccess)
        AssetServices::CreateAssetFile(assetResult.assetNode);
    else
        printf(assetResult.error.c_str());

    // Second Layer
    folderResult = assetTree->CreateFolderNode("Folder2", assetTree->GetRootNode()->GetChildFolderList()[0]);
    if (folderResult.isSuccess)
    {
        AssetServices::CreateFolder(folderResult.folderNode);
    }
    else
    {
        printf(folderResult.error.c_str());
        return;
    }

    assetResult = assetTree->CreateAssetNode(nullptr, "Person2.1", folderResult.folderNode);
    if (assetResult.isSuccess)
        AssetServices::CreateAssetFile(assetResult.assetNode);
    else
        printf(assetResult.error.c_str());

    assetResult = assetTree->CreateAssetNode(nullptr, "Person2.2", folderResult.folderNode);
    if (assetResult.isSuccess)
        AssetServices::CreateAssetFile(assetResult.assetNode);
    else
        printf(assetResult.error.c_str());

    // Third Layer

    folderResult = assetTree->CreateFolderNode("Folder3.1", assetTree->GetRootNode()->GetChildFolderList()[0]->GetChildFolderList()[0]);
    if (folderResult.isSuccess)
    {
        AssetServices::CreateFolder(folderResult.folderNode);
    }
    else
    {
        printf(folderResult.error.c_str());
        return;
    }

    assetResult = assetTree->CreateAssetNode(nullptr, "Person3.1", folderResult.folderNode);
    if (assetResult.isSuccess)
        AssetServices::CreateAssetFile(assetResult.assetNode);
    else
        printf(assetResult.error.c_str());

    folderResult = assetTree->CreateFolderNode("Folder3.2", assetTree->GetRootNode()->GetChildFolderList()[0]->GetChildFolderList()[0]);
    if (assetResult.isSuccess)
    {
        AssetServices::CreateFolder(folderResult.folderNode);
    }
    else
    {
        printf(folderResult.error.c_str());
        return;
    }

    assetResult = assetTree->CreateAssetNode(nullptr, "Person3.2", folderResult.folderNode);
    if (assetResult.isSuccess)
        AssetServices::CreateAssetFile(assetResult.assetNode);
    else
        printf(assetResult.error.c_str());
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

    FolderModificationResult folderResult = AssetServices::RemoveFolder(folderNode, false);
    if (folderResult.isSuccess)
        assetTree->RemoveFolderNode(folderNode, false);
    else
        printf(folderResult.error.c_str());
}

TEST(AssetTest, MoveFolder)
{
    AssetTree* assetTree = AssetServices::FindAssetTree("Content");

    FolderNode* folderNode = assetTree->GetRootNode()->GetChildFolderList()[0]->GetChildFolderList()[0];

    FolderModificationResult folderResult = AssetServices::MoveFolder(folderNode, assetTree->GetRootNode());
    if (folderResult.isSuccess)
        assetTree->MoveFolderNode(folderNode, assetTree->GetRootNode());
    else
        printf(folderResult.error.c_str());
}

TEST(AssetTest, MoveAsset)
{
    AssetTree* assetTree = AssetServices::FindAssetTree("Content");

    AssetNode* assetNode = assetTree->GetRootNode()->GetChildFolderList()[0]->GetChildAssetList()[0];

    AssetModificationResult assetResult = AssetServices::MoveAsset(assetNode, assetTree->GetRootNode());
    if (assetResult.isSuccess)
        assetTree->MoveAssetNode(assetNode, assetTree->GetRootNode());
    else
        printf(assetResult.error.c_str());
}