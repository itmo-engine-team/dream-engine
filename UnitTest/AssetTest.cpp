#include "pch.h"

#include "AssetServices.h"

TEST(AssetTest, CreateAsset)
{
    AssetTree* assetTree = AssetServices::FindAssetTree("Content");
    AssetModificationResult assetStruct = assetTree->CreateAssetNode(nullptr, "Person", assetTree->GetRootNode());

    if (assetStruct.resault)
        AssetServices::CreateAssetFile(assetStruct.assetNode);

    printf(assetStruct.error.c_str());   
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
    FolderModificationResult folderStruct = assetTree->CreateFolderNode("Folder1", assetTree->GetRootNode());
    if(folderStruct.resault)
        AssetServices::CreateFolder(folderStruct.folderNode);
    else
    {
        printf(folderStruct.error.c_str());
        return;
    }

    AssetModificationResult assetStruct = assetTree->CreateAssetNode(nullptr, "Person1", folderStruct.folderNode);
    if (assetStruct.resault)
        AssetServices::CreateAssetFile(assetStruct.assetNode);

    // Second Layer
    folderStruct = assetTree->CreateFolderNode("Folder2", assetTree->GetRootNode()->GetChildFolderList()[0]);
    if (folderStruct.resault)
        AssetServices::CreateFolder(folderStruct.folderNode);
    else
    {
        printf(folderStruct.error.c_str());
        return;
    }

    assetStruct = assetTree->CreateAssetNode(nullptr, "Person2.1", folderStruct.folderNode);
    if (assetStruct.resault)
        AssetServices::CreateAssetFile(assetStruct.assetNode);

    assetStruct = assetTree->CreateAssetNode(nullptr, "Person2.2", folderStruct.folderNode);
    if (assetStruct.resault)
        AssetServices::CreateAssetFile(assetStruct.assetNode);

    // Third Layer

    folderStruct = assetTree->CreateFolderNode("Folder3.1", assetTree->GetRootNode()->GetChildFolderList()[0]->GetChildFolderList()[0]);
    if (folderStruct.resault)
        AssetServices::CreateFolder(folderStruct.folderNode);
    else
    {
        printf(folderStruct.error.c_str());
        return;
    }

    assetStruct = assetTree->CreateAssetNode(nullptr, "Person3.1", folderStruct.folderNode);
    if (assetStruct.resault)
        AssetServices::CreateAssetFile(assetStruct.assetNode);

    folderStruct = assetTree->CreateFolderNode("Folder3.2", assetTree->GetRootNode()->GetChildFolderList()[0]->GetChildFolderList()[0]);
    if (assetStruct.resault)
        AssetServices::CreateFolder(folderStruct.folderNode);
    else
    {
        printf(folderStruct.error.c_str());
        return;
    }

    assetStruct = assetTree->CreateAssetNode(nullptr, "Person3.2", folderStruct.folderNode);
    if (assetStruct.resault)
        AssetServices::CreateAssetFile(assetStruct.assetNode);
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

TEST(AssetTest, MoveFolder)
{
    AssetTree* assetTree = AssetServices::FindAssetTree("Content");

    FolderNode* folderNode = assetTree->GetRootNode()->GetChildFolderList()[0]->GetChildFolderList()[0];

    AssetServices::MoveFolder(folderNode, assetTree->GetRootNode());
    assetTree->MoveFolderNode(folderNode, assetTree->GetRootNode());
}

TEST(AssetTest, MoveAsset)
{
    AssetTree* assetTree = AssetServices::FindAssetTree("Content");

    AssetNode* assetNode = assetTree->GetRootNode()->GetChildFolderList()[0]->GetChildAssetList()[0];

    AssetServices::MoveAsset(assetNode, assetTree->GetRootNode());
    assetTree->MoveAssetNode(assetNode, assetTree->GetRootNode());
}